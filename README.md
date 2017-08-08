# basic-blockchain
A stab at trying some basic blockchain programming.

Following this excellent blog series as I go along:
https://github.com/keeshux/basic-blockchain-programming
http://davidederosa.com/basic-blockchain-programming/

With a little playing along and fiddling with values and outputs to better understand the subject.

- Create new private key: `openssl ecparam -name secp256k1 -genkey -out ec-priv.pem`
- Decode key to show hex: `openssl ec -in ec-priv.pem -text -noout`
- Store public key separately: `openssl ec -in ec-priv.pem -pubout -out ec-pub.pem`
- Decode public key: `openssl ec -in ec-pub.pem -pubin -text -noout`
- Compress public key: `openssl ec -in ec-pub.pem -pubin -text -noout -conv_form compressed`


- Sign message: `openssl dgst -sha256 -sign ec-priv.pem ex-message.txt >ex-signature.der`
- Verify message: `openssl dgst -sha256 -verify ec-pub.pem -signature ex-signature.der ex-message.txt`