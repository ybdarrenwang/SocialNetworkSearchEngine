import tweepy

# == OAuth Authentication ==
#
# This mode of authentication is the new preferred way
# of authenticating with Twitter.

# The consumer keys can be found on your application's Details
# page located at https://dev.twitter.com/apps (under "OAuth settings")
consumer_key="2YIdiuX1g8GyCGu0bkl2w"
consumer_secret="NQm7aC0R7yYNyIgIGp9YkVl5whgqLr7yhNM7n13sCso"

# The access tokens can be found on your applications's Details
# page located at https://dev.twitter.com/apps (located 
# under "Your access token")
access_token="231725785-cKJ1FsH5YJ04wGybnQ21brhWsT6kwb5X7rVPrncM"
access_token_secret="21fOvYK2ZWoKLNVN0avIRxX4ml9e4lr0tTZAhurpDM"

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)

api = tweepy.API(auth)

# If the authentication was successful, you should
# see the name of the account print out
print api.me().name

# If the application settings are set for "Read and Write" then
# this line should tweet out the message to your account's 
# timeline. The "Read and Write" setting is on https://dev.twitter.com/apps
#api.update_status('Updating using OAuth authentication via Tweepy!')
public_tweets = api.friends_timeline()
for tweet in public_tweets:
    t_user = tweet.user
    print t_user.name
    print tweet.text
    print '\n'
