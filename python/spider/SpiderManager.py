# -*- coding: utf-8 -*-
import time
import ItemSpider
import MainPageSpider

class Spidermanager(object):
    def __init__(self):
        pass

    def start(self, url):
        mpsp = MainPageSpider.MeituluMainPageSpider(url)
        ld = mpsp.run()

        name, links = ld["name"], ld["links"]

        print("Main page name: " + name)
        print("Page num: " + str(len(links)))
        print()
        
        time = 0
        i = 0

        for url in links:
            """
            if i > 3:
                break
            """
            i = i + 1
            print("Step " + str(i) + ":")
            isp = ItemSpider.MeituluItemSpider(url)
            totalTime = isp.run()
            time = time + totalTime

        print("Main page name: " + name)
        print("Page num: " + str(len(links)))
        print("Total time: " + str(time))
        

if __name__ == "__main__":
    url = "https://www.meitulu.com/t/sugar-xiaotianxincc/"
    sm = Spidermanager()
    sm.start(url)
