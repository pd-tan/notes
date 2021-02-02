# Main reference
https://www.jetsonhacks.com/2020/08/08/clone-sd-card-jetson-nano-and-xavier-nx/

# Summary
Use balena etcher to flash instead of gunzip
Added progress option to dd

# Software required
balena etcher https://www.balena.io/etcher/

# Advice
Run in tmux and detch if possible as copying take very long. Ensures that program runs even if terminal is closed by accident

# Instruction
## Figure out drive of SD card
1. Plug out SD card
2. ` sudo parted -l` 
3. Plug in SD card
4. ` sudo parted -l`
5. Additional drive should be the SD card. Example `/dev/sdd`

## Set variable
1. Set drive variable: `export CARD_NAME= /dec/sd*` 
2. Set backup file path variable: `export BACKUP_FILE_PATH = *path*`. Example: `export BACKUP_FILE_PATH =~/BACKUP/raspi_backup.img.gz`

## Backup the drive
1. `sudo umount $CARD_NAME`
2. `sudo dd status=progress if=$CARD_NAME conv=sync,noerror bs=64K | gzip -c > $BACKUP_FILE_PATH`

## Restore / Copy
1. Flash using Balena etcher
