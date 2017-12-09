# -*- coding: utf-8 -*-
import requests
import bs4
import re

class MeituluMainPageSpider(object):
    def __init__(self, url, usetmp=True):
        self._url = url
        self._links = []

        self._response = None
        self._soup = None
        self._name = ""

    def isMainPageUrlValid(self, url):
        pattern = re.compile("https://www.meitulu.com/t/\S+/")
        url = url.strip()
        return True if pattern.match(url) else False

    def requestMainPage(self):
        try:
            response = requests.request("GET", self._url)
        except Exception:
            print("Error happened")
        else:
            self._response = response
            self._soup = bs4.BeautifulSoup(response.content, "html.parser")

    def parseMessage(self):
        soup = self._soup
        
        tagName = "div"
        className = "listtags_l"
        tags = soup.find_all(tagName, class_=className)

        child = tags[0].img
        
        self._name = str(child["alt"])

    def parseContent(self):
        itemPattern = re.compile("https://www.meitulu.com/item/\d+\.html")
        soup = self._soup

        tagName = "a"
        limits = { "href": itemPattern }

        tags = soup.find_all(tagName, limits)

        links = [ str(tag["href"]) for tag in tags ]
        links = list(set(links))

        self._links = links
        
                
    def run(self):
        if self.isMainPageUrlValid(self._url):
            self.requestMainPage()
            self.parseMessage()
            self.parseContent()

            return { "name": self._name, "links": self._links }
        else:
            return { "name": "unknown", "links": [] }

if __name__ == "__main__":
    mainPageUrl = "https://www.meitulu.com/t/sugar-xiaotianxincc/"
    s = MeituluMainPageSpider(mainPageUrl)
    print(s.run())



        

