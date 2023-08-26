# Calendar generator
This is simple Gregorian calendar generator coded in c++

## Installation
- download repo
- **make** at root folder

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
