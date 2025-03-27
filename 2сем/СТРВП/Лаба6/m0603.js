var nodemailer = require("nodemailer")

function Send(sender, message){
    let transporter = nodemailer.createTransport({
        service: 'gmail',
        port: 587,
        secure: false,
        auth: {
            user: sender.mail,
            pass: sender.password
        }
    });

    var mailOptions = {
        from: sender.mail,
        to: sender.mail,
        subject: "Laba 6 Module",
        text: message,
        html: `<i>${message}</i>`
    };

    transporter.sendMail(mailOptions, function (error, info) {
        if (error) {
            console.error(error);
            return -1
        } else {
            console.log('Email sent: ' + info.response);
            return 0
        }
    });
}

exports.Send = Send