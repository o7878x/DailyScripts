# -*- coding: utf-8 -*-
import multiprocessing
import requests
import bs4
import re
import os
import time
import math

def workerMethod(downloadUrl, path):
    """ Download a single picture and save it """
    try:
        response = requests.request("GET", downloadUrl)
        picData = response.content
    except Exception:
        print("Error: cannot download picture!")

        with open("./errlinks.txt", "a+") as fe:
            fe.write(downloadUrl)
        return 1 # count lost url
    else:
        with open(path, "wb") as picture:
            picture.write(picData)
        return 0 # count lost url

class MeituluItemSpider(object):
    """ spider for `https://www.meitulu.com` """
    def __init__(self, url):
        self._url = url

        self._response = None # reponse content
        self._count = 0 # total pictures count
        self._name = "" # target model's name
        self._baseUrl = "" # target picture source link
        self._path = ""
        self._vol = ""
        self._lost = 0 # count lost file

    def requestContent(self):
        pattern = re.compile("https://www.meitulu.com/item/")

        if pattern.match(self._url):
            # get suffix string
            self._vol = re.search("\d+", self._url).group(0)

            # request main page of the first url
            self._response = requests.request("GET", self._url)
        else:
            raise IOError("inpurt invalid url")


    def parseMessage(self):
        # get message tag lists from <div class="c_">
        mtag = self._soup.find_all("div", "c_l")[0]
        ptags = mtag.find_all("p")

        # get total count of these pictures
        numTag = ptags[2]
        numStr = str(numTag.string)
        picNum = int(re.search("\d+", numStr).group(0))
        self._count = picNum # save as member

        # get beauty name 
        nameTag = ptags[4]
        if nameTag.a:
            nameStr = nameTag.a
            self._name = str(nameStr.string) # save as member
        else:
            nameStr = str(nameTag.contents[0])
            self._name = re.split("：", nameStr)[1]

        self._name = self._name.strip()

        # get base picture url
        imgtags = self._soup.find_all("img", "content_img")
        self._baseUrl = re.sub("\d+.jpg", "", imgtags[-1]["src"])

        print("-------------------------------------------")
        print("   Model name     : " + self._name)
        print("   Picture links  : " + self._url)

    """
    def requestPic(self, downloadUrl, path):
        r = requests.request("GET", downloadUrl)
        with open(path, "wb") as f:
            f.write(r.content)

    def downloadPic(self):
        if self._baseUrl is not None:
            for i in range(1, self._count+1, 1):
                print("Picture " + str(i) + ":")
                downloadUrl = self._baseUrl + str(i) + ".jpg"
                picName = self._path + str(i) + ".jpg"
                self.requestPic(downloadUrl, picName)
    
    def requestPicEx(self, num):
        downloadUrl = self._baseUrl + str(num) + ".jpg"
        picName = self._path + str(num) + ".jpg"
        rp = requests.request("GET", downloadUrl)
        with open(picName, "wb") as f:
            f.write(rp.content)
    """

    def downloadPicEx(self):
        countRange = range(1, self._count+1, 1)
        argList = [ (self._baseUrl + str(i) + ".jpg",\
                     self._path + str(i) + ".jpg") for i in countRange]

        p = multiprocessing.Pool(10)
        lostLinks = p.starmap(workerMethod, argList)

        total = self._count
        lost = sum(lostLinks)
        get = total - lost

        self._lost = lost
        
        print("   Picture number : " + str(get) + "/" + str(total))

    def createPath(self):
        self._path = "./" + self._name + self._vol + "/"
        if not os.path.exists(self._path):
            os.makedirs(self._path)

    def parseContent(self):
        self._soup = bs4.BeautifulSoup(self._response.content, "html.parser")

    def run(self):
        start = time.time()

        # main process
        self.requestContent()
        self.parseContent()
        self.parseMessage()
        self.createPath()
        self.downloadPicEx()

        end = time.time()
        totalTime = end-start

        print("   Time consumed  : " + str(math.ceil(totalTime)) + "s")
        print("-------------------------------------------")
        print()

        return totalTime

class FileReader(object):
    def __init__(self):
        self.urlList = []

    def read(self, fPath):
        with open(fPath, "w") as f:
            line = f.readline()
            if line is not None and line.length != 0:
                self.urlList.append(line)

    def getUrlList(self):
        return self.urlList


if __name__ == "__main__":
    urlList = [
               "https://www.meitulu.com/item/8255.html",
              ]

    for url in urlList:
        s = MeituluItemSpider(url)
        s.run()

