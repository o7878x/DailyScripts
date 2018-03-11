# -*- coding : utf-8 -*-
import time
import json
import requests

def fetchJson(url):
    headers = { "User-Agent" : "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.13 Safari/537.36" }
    r = requests.get(url, headers)
    return r.json()

def saveNormalJson():
    url = "https://live.fc2.com/contents/allchannellist.php"
    jr = fetchJson(url)
    fn = str(int(time.time())) + ".json"
    with open(fn, "w") as f:
        json.dump(jr, f)

def saveAdultJson():
    url = "https://live.fc2.com/adult/contents/allchannellist.php"
    jr = fetchJson(url)
    fn = str(int(time.time())) + ".json"
    with open(fn, "w") as f:
        json.dump(jr, f)

if __name__ == "__main__":
    saveAdultJson()
