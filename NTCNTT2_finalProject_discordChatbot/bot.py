import discord
import responses

async def send_message(message, user_message, is_private):
    try:
        response = responses.find_answer(user_message)  # Lấy câu trả lời từ hàm find_answer đã nhập
        await message.author.send(response) if is_private else await message.channel.send(response)
    except Exception as e:
        print(e)
        await message.channel.send("Có lỗi xảy ra, vui lòng thử lại sau.")

def run_discord_bot():
    TOKEN = "" #Token của discord bot
    intents = discord.Intents.default()
    intents.message_content = True

    client = discord.Client(intents=intents)

    @client.event
    async def on_ready():
        print(f'{client.user} is now running!')

    @client.event
    async def on_message(message):
        if message.author == client.user:
            return

        username = str(message.author)
        user_message = str(message.content)
        channel = str(message.channel)

        print(f'{username} said: "{user_message}" ({channel})')

        await send_message(message, user_message, is_private=False)

    client.run(TOKEN)