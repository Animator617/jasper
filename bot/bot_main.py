# Work with Python 3.6
import discord
import bot
from commands import help
from commands import cry

#import bot_comands
from bot_comands.say_hello import JS_bot_sayHello

TOKEN = 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
#commands.Bot(command_prefix=",j")

client = discord.Client()

## declaring some variables
'''
jasper_logo = 'I\'m jasper \n' \
              '----------- \n' \
              ' '
'''
jasper_logo1 = "#########################"
jasper_logo2 = "#                        J.A.S.P.E.R                        #"
jasper_logo3 = "#########################"
jasper_logo4 = "."
jasper_logo5 = "               ##################"
jasper_logo6 = "               #                The AI                  #"
jasper_logo7 = "               ##################"


__version__ = "0.0.2"				
start_text = "-------------------------------------------------------\n" \
             " The Artificial Inteligenz  " + "v" + __version__ + "\n" \
             "-------------------------------------------------------\n" \
             "By Animator617 (c) \n"

@client.event
async def on_message(message):
    if message.content.startswith('j!'):
        if message.content == 'j!hello':
            channel = message.channel
            await channel.send('Say hello!')
            print('**hello**')
            def check(m):
                return m.content == 'hello' and m.channel == channel

            msg = await client.wait_for('message', check=check)
            await channel.send('Hello {.author}!'.format(msg))

        elif message.content == 'j!by':
            channel = message.channel
            await channel.send('Say by!')
            print('**by**')
            def check(m):
                return m.content == 'by' and m.channel == channel


            msg = await client.wait_for('message', check=check)
            await channel.send('By {.author}!'.format(msg))

        elif message.content == 'j!who are you':
            channel = message.channel
            await channel.send(jasper_logo1)
            await channel.send(jasper_logo2)
            await channel.send(jasper_logo3)
            await channel.send(jasper_logo4)
            await channel.send(jasper_logo5)
            await channel.send(jasper_logo6)
            await channel.send(jasper_logo7)
            
            await channel.send(start_text)
            await channel.send('and who are you')
            print('who are you?')
            def check(m):
                return m.content == 'who are you' and m.channel == channel

            msg = await client.wait_for('message', check=check)
            await channel.send('who are you {.author}!'.format(msg))
        elif message.content == 'j!cry':
            await channel.send(cry_content)
            print('** cry **')
            def check(m):
                return m.content == 'cry' and m.channel == channel

            msg = await client.wait_for('message', check=check)
            await channel.send('cry {.author}!'.format(msg))

        elif message.content == 'j!help' or message.content == 'j1 help' or message.content == 'j!help me' or message.content == 'j! help me':
            await channel.send(help.help_text)
            print('** help **')
            def check(m):
                return m.content == 'help' and m.channel == channel

            msg = await client.wait_for('message', check=check)
            await channel.send('help {.author}!'.format(msg))
        
            

'''
@client.event
async def on_message(message):
    # we do not want the bot to reply to itself
    if message.author == client.user:
        return



    if message.content.startswith('!hello'):
        msg = 'Hello {0.author.mention}'.format(message)
        await client.send_message(message.channel, msg)
'''

@client.event
async def on_ready():
    print('Logged in as')
    print(client.user.name)
    print(client.user.id)
    print('------')

client.run(TOKEN)
