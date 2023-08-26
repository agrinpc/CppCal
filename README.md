# Calendar generator
This is a simple **Gregorian** calendar generator wirtten in c++

## Installation
- download repo
- use **make** at root folder

## Usage
```
./calgen [OPTIONS]
```

### List of options
```
<number>               : year (can be multipe years)
<[start_year,end_year] : range of years
-t <title>             : add custom title
-d <text>              : add custom description
-n <name>              : name of the output file (without .html)
-fs <font-size>        : font-size of title
--noexpand             : produce single year (no +-1 year)
--sort                 : sort input years
```
### Examples
```
./calgen
```
```
./calgen 1998 2011 -d "sample text" -t title -fs 80 --sort 2015 [1800,1850]
```
