import urllib.request as request
import urllib.parse as parse
import re
import bs4 as bs 
import datetime
from bs4 import SoupStrainer

start = datetime.datetime.now()

url = 'http://www.metacritic.com/search'
values = {'search_term':'horizon zero dawn',
		  'search_filter':'all'}
parse_only = SoupStrainer(id='main')
data = parse.urlencode(values).encode('utf-8')
req = request.Request(url,data,headers={'user-agent':'Mozilla/5.0'})
resp = request.urlopen(req).read()
soup = bs.BeautifulSoup(resp,'lxml',parse_only=parse_only)
results = [result for result in soup.find_all('li',class_='result') if 'Game' in result.find('div',class_='result_type').text]
print(len(results))

print('Total run time: ',datetime.datetime.now()-start)

