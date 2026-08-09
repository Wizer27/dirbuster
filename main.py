import argparse
import requests

parser = argparse.ArgumentParser(description='Lux directory travesal')
parser.add_argument('-f', '--file', type=str, help='file with dirrectories')
parser.add_argument('-u','--url',type=str,help = "url to attack")
parser.add_argument('-j','--json',type=str,help = "get json response or no")
parser.add_argument("-c","--codes",type = list,help = "allowed codes")


args = parser.parse_args()



VERSION = "v1.0.0"

BANNER = r"""
    __    __  ___  __ ________  ____________
/ /   / / / / |/ // ____/ / / /__  /__  /
/ /   / / / /|   // /_  / / / /  / /  / /
/ /___/ /_/ //   |/ __/ / /_/ /  / /__/ /__
/_____/\____//_/|_/_/    \____/  /____/____/  {version}
"""


def banner() -> None:
    print(BANNER.format(version=VERSION))


    
def old_version():
    if not args.file or not args.url:
        raise KeyError("Wrong argument")
    else:
        with open(args.file,"r") as file:
            data = file.read()
        for i in data.split('\n'):
            try:
                resp = requests.get(args.url + i)
                if args.codes:
                    if resp.status_code in args.codes:
                        print(f"[+] {args.url + i}")
                        print(f"[+] Status_code: {resp.status_code}")
                        if args.json:
                            print(f"JSON : {resp.json()}")
                else:
                    if resp.status_code not in [404,401]:
                        print(f"[+] {args.url + i}")
                        print(f"[+] Status_code: {resp.status_code}")
                        if args.json:
                            print(f"JSON : {resp.json()}")

            except Exception as e:
                print(f"Error : {e}")


def ffuf_style():
    if not args.file or not args.url:
        raise KeyError("Wrong argument")
    else:
        with open(args.file,"r") as file:
            data = file.read()
        
        for dir in data.split('\n'):
            try:
                url = args.url.replace("FUZZ",dir)
                resp = requests.get(url)
                if args.codes:
                    if resp.status_code in args.codes:
                        print(f"[+] {url}")
                        print(f"[+] Status_code: {resp.status_code}")
                        if args.json:
                            print(f"JSON : {resp.json()}")
                else:
                    if resp.status_code not in [404,401]:
                        print(f"[+] {url}")
                        print(f"[+] Status_code: {resp.status_code}")
                        if args.json:
                            print(f"JSON : {resp.json()}")

            except Exception as e:
                print(f"[+] ERROR : {e}")

if __name__ == "__main__":
    banner()
    ffuf_style()

