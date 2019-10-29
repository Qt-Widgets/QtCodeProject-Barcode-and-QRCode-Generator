#ifndef QCodePrinter_H
#define QCodePrinter_H

#include <QObject>
#include <QColor>

#define CODE128_B_START 104
#define CODE128_STOP 106

class QCodePrinter : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief QCodePrinter
     * @param parent
     * Constructor
     */
    explicit QCodePrinter(QObject *parent = nullptr);

    /**
     * @brief printBarcode
     * @param barcodeText
     * @param size
     * @param color
     * @return Image of the barcode
     */
    QImage printBarcode(const QString &barcodeText, const QSize &size, const QColor &color);

    /**
     * @brief printQrcode
     * @param qrcodeText
     * @param qrcodeSize
     * @param color
     * @return Image of the QR code
     */
    QImage printQrcode(const QString &qrcodeText, const QSize &qrcodeSize, const QColor &color = Qt::black);
private:
    /**
     * @brief encodeBarcode
     * @param code
     * @return Adds start/check/stop characters to the code
     */
    QString encodeBarcode(const QString &code);

    /**
     * @brief calculateCheckCharacter
     * @param code
     * @return Calculates the checksum character from the code
     */
    int calculateCheckCharacter(const QString &code);

    /**
     * @brief codeToChar
     * @param code
     * @return The code
     */
    int codeToChar(int code);

    /**
     * @brief charToCode
     * @param ch
     * @return The character
     */
    int charToCode(int ch);
};

#endif // QCodePrinter_H


