#!/bin/bash
export ACE_ILP_ROOT=$2
{
{
cd ../Models/train/$1/qsa &&
${ACE_ILP_ROOT}/bin/ace <<EOD
tilde
EOD
} && {
cd ../oqsa &&
${ACE_ILP_ROOT}/bin/ace <<EOD
tilde
EOD
echo
echo "success"
exit 0
}
} || {
exit 1
}

