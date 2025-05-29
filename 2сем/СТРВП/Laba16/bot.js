const TelegramBot = require('node-telegram-bot-api');

//токен, полученный от BotFather
const token = '7635513394:AAGqfkHXSXIfdP0UcNoUBy_9vJJ2XbX-0wU';

// Создаем экземпляр бота с режимом Long Polling
const bot = new TelegramBot(token, { polling: true });

// Обработчик входящих сообщений
bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  const messageText = msg.text;

  // Проверяем, что сообщение не является командой (например, /start)
  if (messageText && !messageText.startsWith('/')) {
    // Отправляем echo-ответ
    bot.sendMessage(chatId, `echo: ${messageText}`);
  }
});

// Обработчик ошибок polling
bot.on('polling_error', (error) => {
  console.error('Ошибка polling:', error);
});

console.log('Бот запущен...');