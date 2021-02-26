// Copyright (c) 2011-2014 The Bitcoinrtx developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOINRTX_QT_BITCOINRTXADDRESSVALIDATOR_H
#define BITCOINRTX_QT_BITCOINRTXADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BitcoinrtxAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BitcoinrtxAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Bitcoinrtx address widget validator, checks for a valid bitcoinrtx address.
 */
class BitcoinrtxAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BitcoinrtxAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BITCOINRTX_QT_BITCOINRTXADDRESSVALIDATOR_H
