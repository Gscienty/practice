#coding=utf-8
"""
Usage: ticket.py <from> <to> <time> [<purpose>]
"""
from docopt import docopt
from prettytable import PrettyTable
import requests
import re
import warnings
warnings.filterwarnings("ignore")

station_info = requests.get('https://kyfw.12306.cn/otn/resources/js/framework/station_name.js?station_version=1.8964', verify=False)

stations_text = re.findall(r'\@(.*?\d+)', station_info.text)

station = {}
for item in stations_text:
    item_arr = item.split('|')
    station[item_arr[3]] = { 'code' : item_arr[2], 'chinese' : item_arr[1] }

arguments = docopt(__doc__)

from_station = station[arguments['<from>']]
to_station = station[arguments['<to>']]
train_time = arguments['<time>']
purpose = arguments['<purpose>']
if purpose == None:
    purpose = 'ADULT'

print u'查询 日期为 \033[92m' + train_time +u' \033[0m的 \033[95m' + from_station['chinese'] + u'站 \033[0m到 \033[95m' + to_station['chinese'] + u'站 \033[0m的火车票'

query_request = requests.get('https://kyfw.12306.cn/otn/lcxxcx/query?purpose_codes=' + purpose + '&queryDate=' + train_time + '&from_station=' + from_station['code'].upper() + '&to_station=' + to_station['code'].upper(), verify=False)

ticket_data = query_request.json()['data']

if ticket_data.has_key('message'):
    print ticket_data['message']
    exit()
ticket_data = ticket_data['datas']

ticket_list = []


print '-----------------------------------------------------------------------------------------------------------------------------'
print u'车次  |          出发/到达车站       | 始发/终到时间 | 历时  | 商务座 | 特等座 | 一等座 | 二等座 | 软卧 | 硬卧 | 硬座 | 无座 |'
print '-----------------------------------------------------------------------------------------------------------------------------'

page_size = 10

for ticket in ticket_data:
    if page_size == 0:
        raw_input('')
        print '-----------------------------------------------------------------------------------------------------------------------------'
        print u'车次  |          出发/到达车站       | 始发/终到时间 | 历时  | 商务座 | 特等座 | 一等座 | 二等座 | 软卧 | 硬卧 | 硬座 | 无座 |'
        print '-----------------------------------------------------------------------------------------------------------------------------'
        page_size = 10
    page_size = page_size - 1
    current = [
        ticket['station_train_code'],
        ticket['from_station_name'], 
        ticket['to_station_name'],
        ticket['start_time'],
        ticket['arrive_time'],
        ticket['lishi'],
        ticket['swz_num'].replace(u'无', '--'),
        ticket['tz_num'].replace(u'无', '--'),
        ticket['zy_num'].replace(u'无', '--'),
        ticket['ze_num'].replace(u'无', '--'),
        ticket['rw_num'].replace(u'无', '--'),
        ticket['yw_num'].replace(u'无', '--'),
        ticket['yz_num'].replace(u'无', '--'),
        ticket['wz_num'].replace(u'无', '--')
    ]

    print u'\033[90m{:6}\033[0m|从\033[94m {:9} \033[0m至\033[93m {:9}\033[0m| \033[81m{:6}~ \033[82m{:6}\033[0m| {:6}|    {:4}|    {:4}|    {:4}|    {:4}|  {:4}|  {:4}|  {:4}|  {:4}|'.format(current[0], current[1], current[2],current[3], current[4], current[5], current[6], current[7], current[8], current[9], current[10], current[11], current[12], current[13])
    print '----------------------------------------------------------------------------------------------------------------------------'
    
