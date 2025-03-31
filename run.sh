## start and put alias of the lang things

$pwd = $(pwd)

## copy things to root


## create dirs first
mkdir /usr/local/bin/supac
mkdir /usr/local/bin/supac/bin
mkdir /usr/local/bin/supac/libs

## create some files too
echo $(cat ./run.sh) >> /usr/local/bin/supac/supac.sh

echo "LANGUAGE::VERSION=1.1" >> /usr/local/bin/supac/supac.env
echo "LANGUAGE::IS_BETA=True" >> /usr/local/bin/supac/supac.env

## copy them now
cp ./supac /usr/local/bin/supac/bin/

cp ./assets /usr/local/bin/supac
cp ./stdlib /usr/local/bin/supac/libs

cp ./bin/supac_pm /usr/local/bin/supac/bin/

cp ./bin/supac_langmang /usr/local/bin/supac/bin/

## for language itself

echo "alias supacc='/usr/local/bin/supac/bin/supac'" >> ~/.bashrc
echo "alias supacc='/usr/local/bin/supac/bin/supac'" >> ~/.zshrc

## for language manager

echo "alias supac='/usr/local/bin/supac/bin/supac_langmang'" >> ~/.bashrc
echo "alias supac='/usr/local/bin/supac/bin/supac_langmang'" >> ~/.zshrc

## for package manager

echo "alias papm='/usr/local/bin/supac/bin/supac_papm'" >> ~/.bashrc
echo "alias papm='/usr/local/bin/supac/bin/supac_papm'" >> ~/.zshrc