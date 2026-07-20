import argparse
import requests

parser = argparse.ArgumentParser(description='Lux directory travesal')
parser.add_argument('-f', '--file', type=str, help='file with dirrectories')
parser.add_argument('-u','--url',type=str,help = "url to attack")
parser.add_argument('-j','--json',type=str,help = "get json response or no")


args = parser.parse_args()

    

if not args.file or not args.url:
    raise KeyError("Wrong argument")
else:
    with open(args.file,"r") as file:
        data = file.read()
    for i in data.split('\n'):
        try:
            resp = requests.get(args.url + i)
            if resp.status_code != 404 and resp.status_code != 401:
                print(f"[+] {args.url + i}")
                print(f"[+] Status_code: {resp.status_code}")
                if parser.json:
                    print(f"JSON : {resp.json}")
        except Exception as e:
            print(f"Error : {e}")