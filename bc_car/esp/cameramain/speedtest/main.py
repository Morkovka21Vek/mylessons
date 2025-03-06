import serial
import traceback
import socket
import os
import sys
import argparse
import time

data = "-100,110\n"

def init_parser():
    parser = argparse.ArgumentParser(description='test speed')
    parser.add_argument('-d', '--device', type=str, help='path to device', default="/dev/ttyUSB0")
    parser.add_argument('-u', '--url', type=str, help='url to send data(\"domen port path\")', default="192.168.4.1 80 /uart")
    parser.add_argument('-b', '--baudrate', type=int, help='serial speed', default=9600)
    parser.add_argument('-o', '--only', help='show result only', action='store_true')
    parser.add_argument('-c', '--count', help='repeat count', type=int, default=100)
    return parser.parse_args()

def main(args):
    results = []
    try:
        serialPort = serial.Serial(
                port=args.device, baudrate=args.baudrate, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
        )
    except Exception as e:
        if not args.only:
            print('ERROR:\n', traceback.format_exc())
        exit(1)

    clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientsocket.connect((args.url.split(' ')[0], int(args.url.split(' ')[1])))

    for _ in range(args.count):
        serialPort.reset_input_buffer()
        time_start = time.time()
        clientsocket.send(f"POST {args.url.split(' ')[2]} HTTP/1.1\r\nHost: 192.168.4.1\r\nUser-Agent: python speedtester\r\nContent-Length: {len(data)}\r\nAccept: */*\r\n\r\n{data}".encode())

        while True:
            if (serialPort.in_waiting >= len(data)):
                time_end = time.time()
                break

        if args.only:
            print((time_end - time_start)*1000)
        else:
            print(f"({time_end} - {time_start})*1000 = {(time_end - time_start)*1000}")
            print(clientsocket.recv(1024))
            print(serialPort.readline())
        results.append(round((time_end - time_start)*1000, 2))

    clientsocket.close()
    print("Mean: ", sum(results)/len(results))


if __name__ == "__main__":
    args = init_parser()
    main(args)
