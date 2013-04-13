#!/bin/bash
#-------------------------------------------------------------------------------
#
# BIGMENU - Een voorbeeld van een wat uitgebreidere shell file
#
# Deze versie is bedoeld voor een System V-omgeving:
# - Het commando "tput" wordt gebruikt voor terminalbesturing
# - De System V-stijl uitvoer van "ps" wordt verondersteld
#
# Voor gebruik met een Berkeley-stijl ps-output is op dit punt een kleine
# aanpassing nodig.
#
#-------------------------------------------------------------------------------
trap `wait; continue` 2
LOGNAME=`who am i | awk `{ print $1 }` `
LOGNAME=echo $LOGNAME | sed `s/^.*!//` `Linux: strip tot uitroepteken`
cd `grep "LOGNAME:" /etc/passwd | awk `{ FS=":"} { print $6}` `
eval `grep TERM= .profile`
export TERM
CLR="`tput clear`"
BOLD="`tput smso`"
NORMAL="`tput rmso`"
echo $CLR
echo '
Dit is een voorbeeld van een klein menu

U kunt enkele commandos op gebied van file-management, disk-management en 
proces-management uitvoeren.
Het bijbehorende UNIX-commando wordt uit vraag en antwoord samengesteld
en zal u telkens getoond worden.
U kunt een UNIX-commando ook direct ingeven.'
echo "
huidige directory: `pwd`"
echo 
echo 'Geef <RETURN> om verder te gaan' ; read answ
while true 	#hoofd-loop
do
	echo $CLR
	echo 'U kunt:
FILE-SYSTEEM COMMANDOS 	1) kijken welke files er zijn
			2) uitgebreide boekhoud-info van files opvragen
			3) het soort van een bestand bepalen
			4) kijken wat er in een file staat
			5) files weggooien
			6) een kopie van een file maken
			7) naar een andere directory gaan
			8) een nieuwe directory aanmaken
			9) een bestaande directory weggooien

DISK-GEBRUIK COMMANDOS	11) opvragen vrijde disk-ruimte
			12) opvragen disk-ruimte onder directory
			13) overzicht disk-ruimte onder directory

PROCES-COMMANDOS	21) kijken wie er ingelogd is
			22) kijken welke processen nu voor uzelf actief zijn
			23) kijken welke processen systeemwijd actief zijn
			24) een proces stoppen

DIVERSEN		90) een bestand editen
			91) naar UNIX shell gaan
			99) met dit menu stoppen'
	echo 'geef uw keuze (nummer of !<UNIX-commando>: \c)'
	read KEUZE
	case "$KEUZE" in 
	1) 	echo $CLR ; echo "${BOLD}UNIX-commando: ls -CF ${NORMAL}"
		ls -CF
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	2) 	echo $CLR ; echo "${BOLD}UNIX-commando: ls -l %{NORMAL}"
		echo ' PROT-MODE 	EIG	GROEP	LENGTE MOD-TIJD		NAAM'
		ls -l | pg
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	3)
		echo $CLR
		echo 'Geef de naam van de file waarvan u het soort wilt bepalen: \c'
		if test -r "$NAAM 2>/dev/null"
		then
			echo "${BOLD}UNIX-commando: file $NAAM ${NORMAL}"
			echo
			file $NAAM
		else
			echo 'Sorry, file bestaat niet of kan niet door u gelezen worden'
		fi
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	4)
		echo 'test1'
		;;
	esac
done
