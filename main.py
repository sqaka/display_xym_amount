import requests
import serial
import time

NODE_URL = "http://00fabf14.xym.stir-hosyu.com:3000"
ADDRESS = "NAWZZXXNHUX6FQRARGO4VCX6M6HCCKUOYNILNVQ"
ARD_PATH = '/dev/cu.usbserial-1140'
SAVE_AMOUNT = 'amount.txt'


def get_past_amount():
    with open(SAVE_AMOUNT, mode='r') as file:
        past_amount = int(file.read())

    return past_amount


def get_xym_amount():
    req = requests.get(NODE_URL + '/accounts/' + ADDRESS).json()
    xym_amount = [mosaics.get('amount')
                  for mosaics in req['account']['mosaics']]
    xym_amount = int("".join([str(n) for n in xym_amount]))

    return xym_amount


def calc_throw_amount(past_amount, xym_amount):
    throw_mosaic = xym_amount - past_amount
    throw_amount = throw_mosaic / 1000000
    if throw_amount >= 1:
        send_info(throw_amount)

    return throw_amount


def send_info(throw_amount):
    with serial.Serial(ARD_PATH, 9600, timeout=10) as ser:
        throw_amount = ('{}\n'.format(int(throw_amount)))
        byte_amount = throw_amount.encode('utf-8')
        ser.write(byte_amount)


def save_xym_amount(xym_amount):
    with open(SAVE_AMOUNT, mode='w') as file:
        file.write(str(xym_amount))


def main():
    while True:
        past_amount = get_past_amount()
        xym_amount = get_xym_amount()
        calc_throw_amount(past_amount, xym_amount)
        # save_xym_amount(xym_amount)
        time.sleep(15)


if __name__ == '__main__':
    main()
