# basic-blockchain
A stab at trying some basic blockchain programming.


Following this blog series as I go along:
https://github.com/keeshux/basic-blockchain-programming
http://davidederosa.com/basic-blockchain-programming/


Create new private key: `openssl ecparam -name secp256k1 -genkey -out ec-priv.pem`
Decode key to show hex: `openssl ec -in ec-priv.pem -text -noout`

Store public key separately: `openssl ec -in ec-priv.pem -pubout -out ec-pub.pem`
Decode public key: `openssl ec -in ec-pub.pem -pubin -text -noout`

Compress public key: `openssl ec -in ec-pub.pem -pubin -text -noout -conv_form compressed`