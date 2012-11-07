# -*- coding: utf-8 -*-
import sys
sys.path.append('plurk_oauth/')
from PlurkAPI import PlurkAPI
import getopt
import json

def usage():
    print '''Help Information:
    -h: Show help information
    '''

if __name__ == '__main__':
    try:
        opts, args = getopt.getopt(sys.argv[1:], "ho:v", ["help", "output="])
    except getopt.GetoptError, err:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)
    file = open('API.keys', 'r+')
    data = json.load(file)
    plurk = PlurkAPI(data["CONSUMER_KEY"], data["CONSUMER_SECRET"])
    if data.get('ACCESS_TOKEN'):
        plurk.authorize(data["ACCESS_TOKEN"],data["ACCESS_TOKEN_SECRET"])
    else:
        plurk.authorize()
        data["ACCESS_TOKEN"] = plurk._oauth.oauth_token['oauth_token']
        data["ACCESS_TOKEN_SECRET"] = plurk._oauth.oauth_token['oauth_token_secret']
        json.dump(data,file)

    content = '中文測試 OAuth API'
    if len(sys.argv) > 1:  
        content = sys.argv[1]
    qualifier = 'says'
    if len(sys.argv) > 2:  
        qualifier = sys.argv[2]
    #print plurk.callAPI('/APP/Timeline/plurkAdd', {
     #   'content': content,
      #  'qualifier': qualifier } )
    

    query = "畢業"

    plurks = plurk.callAPI('/APP/Timeline/getPlurks')

    users = plurks["plurk_users"]
    for p in plurks["plurks"]:
        owner_id = p["owner_id"]
        id_user = users[str(owner_id)]
        print id_user['nick_name'] +' '+ id_user['display_name']
        print p["content"]
