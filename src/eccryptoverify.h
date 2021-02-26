// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoinrtx developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOINRTX_ECCRYPTOVERIFY_H
#define BITCOINRTX_ECCRYPTOVERIFY_H

#include <vector>
#include <cstdlib>

class uint256;

namespace eccrypto {

bool Check(const unsigned char *vch);
bool CheckSignatureElement(const unsigned char *vch, int len, bool half);

} // eccrypto namespace

#endif // BITCOINRTX_ECCRYPTOVERIFY_H
