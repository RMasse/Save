#!/bin/bash

if [[ $# -ne 1 ]];then
        echo "Mauvais nombre d'arguments"
        echo "Usage: $0 nom_user"
        exit 1
fi
if grep -q "^$1:" /etc/passwd
then
        echo "L'utilisateur $1 est défini sur le système"
else
        echo "L'utilisateur $1 n'est pas défini sur le système"
fi
exit 0


