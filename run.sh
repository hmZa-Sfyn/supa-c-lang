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

## for language itself

echo "alias supacc='/usr/local/bin/supac/bin/supac'" >> ~/.bashrc
echo "alias supacc='/usr/local/bin/supac/bin/supac'" >> ~/.zshrc

## for language manager

## for package manager