#include "qcodeprinter.h"
#include "qrcode.h"
#include <QPainter>
#include <QImage>
#include <QFontDatabase>
#include <QFont>

QCodePrinter::QCodePrinter(QObject *parent)
    : QObject(parent)
{
}

QImage QCodePrinter::printBarcode(const QString &barcodeText, const QSize &size, const QColor &color)
{
    QImage img(size, QImage::Format_ARGB32);
    QPainter painter(&img);
    painter.setBrush(color);
    painter.setPen(color);
    QRect barcodeRect = QRect(0, 0, size.width(), size.height());
    const int id = QFontDatabase::addApplicationFont(":/code128.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont barcodefont = QFont(family, 46, QFont::Normal);
    barcodefont.setLetterSpacing(QFont::AbsoluteSpacing,0.0);
    painter.setFont(barcodefont);
    QString arr = encodeBarcode(barcodeText);
    painter.drawText(barcodeRect, Qt::AlignCenter, arr);
    painter.end();
    return img;
}

QImage QCodePrinter::printQrcode(const QString &qrcodeText, const QSize &qrcodeSize, const QColor &color)
{
    QImage img(qrcodeSize, QImage::Format_ARGB32);
    QPainter painter(&img);
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(qrcodeText.toUtf8().constData(), qrcodegen::QrCode::Ecc::LOW);
    const int s = qr.getSize() > 0 ? qr.getSize() : 1;
    const double w = qrcodeSize.width();
    const double h = qrcodeSize.height();
    const double aspect = w / h;
    const double size = ((aspect > 1.0) ? h : w);
    const double scale = size / (s + 2);

    // NOTE: For performance reasons my implementation only draws the foreground parts in supplied color.
    // It expects background to be prepared already (in white or whatever is preferred).
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    for (int y = 0; y < s; ++y)
    {
        for (int x = 0; x < s; ++x)
        {
            const int color = qr.getModule(x, y);  // 0 for white, 1 for black
            if (0 != color)
            {
                const double rx1 = (x + 1) * scale;
                const double ry1 = (y + 1) * scale;
                QRectF r(rx1, ry1, scale, scale);
                painter.drawRects(&r,1);
            }
        }
    }
    return img;
}

QString QCodePrinter::encodeBarcode(const QString &code)
{
    QString encoded;

    // start set with B Code 104
    encoded.prepend(QChar(codeToChar(CODE128_B_START)));
    encoded.append(code);
    encoded.append(QChar(calculateCheckCharacter(code)));

    // end set with Stop Code 106
    encoded.append(QChar(codeToChar(CODE128_STOP)));
    return encoded;
}

int QCodePrinter::calculateCheckCharacter(const QString &code)
{
    // convert code to utf8
    QByteArray encapBarcode(code.toUtf8());

    // calculate check character

    // the sum starts with the B Code start character value
    long long sum = CODE128_B_START;
    int weight = 1; // Initial weight is 1

    foreach(char ch, encapBarcode)
    {
        // calculate character code
        const int code_char = charToCode(int(ch));

        // add weighted code to sum
        sum += code_char * weight;

        weight++; // increment weight
    }

    // the check character is the modulo 103 of the sum
    int remain = sum%103;

    // calculate the font integer from the code integer
    if (remain >= 95)
    {
        remain += 105;
    }
    else
    {
        remain += 32;
    }
    return remain;
}

int QCodePrinter::codeToChar(int code)
{
    return code + 105;
}

int QCodePrinter::charToCode(int ch)
{
    return ch - 32;
}
