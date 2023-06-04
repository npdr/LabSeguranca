--- Program updated by AOCard (2021, Aria Cardoso)      ---
--- Tested on latest Arch Linux (07/2021) on GCC v11.1.0 ---

--- Program created by Pedro Henrique Nieuwenhoff, 2020  ---
--- NUSP: 10377729 ---

Running the scanner:

$ make all
$ ./scan "address_to_scan" "from_port" "to_port"

Results:

$ ./scan 192.168.0.1 0 10000
> domain	53/tcp [OPEN]
> http	80/tcp [OPEN]
> https	443/tcp [OPEN]
> commplex-main	5000/tcp [OPEN]
> personal-agent	5555/tcp [OPEN]
> sunproxyadmin	8081/tcp [OPEN]
> us-cli	8082/tcp [OPEN]

System information:

Compiler: gcc (GCC) 10.2.0
Linux: Manjaro 20.1, Linux 4.14.197-1-MANJARO
