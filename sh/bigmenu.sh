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
	2) 	echo $CLR ; echo "${BOLD}UNIX-commando: ls -l ${NORMAL}"
		echo ' PROT-MODE 	EIG	GROEP	LENGTE MOD-TIJD		NAAM'
		ls -l | pg
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	3)	echo $CLR
		echo "Geef de naam van de file waarvan u het soort wilt bepalen: \c"
		read NAAM
		if test -r "$NAAM" 2>/dev/null
		then
			echo "${BOLD}UNIX-commando: file $NAAM ${NORMAL}"
			echo
			file $NAAM
		else
			echo 'Sorry, file bestaat niet of kan niet door u gelezen worden'
		fi
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	4) 	echo $CLR
		echo 'Geef de naam van de file waarvan u het soort wilt bepalen: \c'
		read NAAM
		if test -r "$NAAM" 2>/dev/null
		then
			echo "${BOLD}UNIX-commando: file $NAAM ${NORMAL}"
			echo
			pr -80 -h "$CLR file: $NAAM" $NAAM | pg
		else
			echo 'Sorry, file bestaat niet of kan niet door u gelezen worden'
		fi
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	5)	echo $CLR
		echo "Geef de naam van de file die u wilt weggooien: \c"
		read NAAM 
		if test -f "$NAAM" 2>/dev/null
		then
			echo "weet u zeker dat U $NAAM wilt weggooien (j/n): \c"
			read KEUZE
			case KEUZE in
			j*)
				echo "${BOLD}UNIX-commando: rm $NAAM ${NORMAL}"
				rm -f $NAAM 2>/dev/null
				if test -f "$NAAM" 2>/dev/null
				then
					echo $NAAM kon niet door u weggegooid worden
				else
					echo $NAAM weggegooid
				fi
				echo 'Geef <RETURN> om verder te gaan' ; read answ
				;;
			*)
				echo $NAAM niet weggegooid
				echo 'Geef <RETURN> om verder te gaan' ; read answ
				;;
			esac
		else
			echo $NAAM bestaat niet
			echo 'Geef <RETURN> om verder te gaan' ; read answ
		fi
		;;
	6)
		echo $CLR
		echo 'Geef de naam van de file waarvan u een kopie wilt maken: \c'
		read NAAM
		if test -r "$NAAM" 2>/dev/null
		then
			echo 'Geef de naam van het (nieuwe) kopie-bestand: \c'
			read NAAM2
			if test -f "$NAAM2" 2>/dev/null
			then
				echo "$NAAM2" 2>/dev/null
				echo Gooi eerst bestand $NAAM2 weg '(optie 4)'
				echo 'Geef <RETURN> om verder te gaan' ; read answ
			else
				echo ${BOLD}UNIX-commando: cp $NAAM $NAAM2 ${NORMAL}
				if cp $NAAM $NAAM2 2>/dev/null
				then
					echo kopie is gemaakt
				else
					echo kopie kon niet gemaakt worden
				fi
				echo 'Geef <RETURN> om verder te gaan' ; read answ
			fi
		else
			echo $NAAM bestaat niet of kan niet gelezen worden
			echo U kunt dus ook geen kopie maken
			echo 'Geef <RETURN> om verder te gaan' ; read answ
		fi
		;;
	7)	echo $CLR
		echo "Huidige directory: `pwd`"
		echo 'geldige subdirectories zijn:\n'
		ls -F | grep '/$' | pr -4 -t -l1 -w80 2>/dev/null
		echo '\nof ^ om directory naar boven te gaan'
		echo 'Geef uw keuze: \c'
		read SUBDIR
		case $SUBDIR in
		\^)	SUBDIR=..
			;;
		esac
		if (cd $SUBDIR) 2>/dev/null
		then
			echo "${BOLD}UNIX-commando: cd $SUBDIR ${NORMAL}"
			cd $SUBDIR
			echo "Huidige directory is nu: `pwd`"
			echo "Geef <RETURN> om verder te gaan" ; read answ
		else
			echo "$SUBDIR bestaat niet of afgesloten voor u"
			echo 'Geef <RETURN> om verder te gaan' ; read answ
		fi
		;;
	8)	echo $CLR
		echo 'Geef de naam van de directory die u wilt maken'
		read NAAM
		if test -f "$NAAM" -o -d "$NAAM" 2>/dev/null
		then
			echo "Sorry, $NAAM is al een bestaande file of directory"
		else
			echo "${BOLD}UNIX-commando: mkdir $NAAM ${NORMAL}"
			if mkdir $NAAM 2>/dev/null
			then
				echo "$NAAM als nieuwe directory geinstalleerd"
			else
				echo "Sorry, $NAAM kan (hier) niet gemaakt worden"
			fi
		fi
		echo 'Geef <RETURN> onm verder te gaan' ; read answ
		;;
	9)	echo $CLR
		echo 'Geef de naam van de directory die u wilt weggooien: \c'
		read NAAM
		if test -d "$NAAM" 2>/dev/null
		then
			if [ `ls -a $NAAM | wc -l ` = 2 ]
			then
				echo "${BOLD}UNIX-commando: rmdir $NAAM ${NORMAL}"
				if rmdir $NAAM 2>/dev/null
				then
					echo "$NAAM verwijderd"
				else
					echo "Sorry, u mag $NAAM niet verwijderen"
				fi
			else
				echo "Waarschuwing: er staan nog bestanden in $NAAM"
				echo "Weet u zeker dat $NAAM en alles daaronder"
				echo "verwijderd meot worden (j/n): \c"
				read KEUZE
				case KEUZE in
				j*)
					echo "${BOLD}UNIX-commando: rm -rf $NAAM ${NORMAL}"
					if rm -rf $NAAM 2>/dev/null
					then
						echo $NAAM weggegooid
					else
						$NAAM kon niet door u verwijderd worden
					fi
					;;
				*)	echo $NAAM niet weggegooid
					;;
				esac
			fi
		else
			echo "Sorry, $NAAM is geen directory"
		fi
		echo 'Geef <RETURN> om verder te gaan' ; read answ 
		;;
	11)	echo $CLR
		echo "${BOLD}UNIX-commando: df ${NORMAL}"
		echo
		df
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	12) 	echo $CLR
		echo 'Geef de naam van de directory: \c'
		read NAAM
		if test -d "$NAAM" 2>/dev/null
		then
			echo "${BOLD}UNIX-commando: du -s $NAAM ${NORMAL}"
			echo
			echo "BLOKKEN	NAAM"
			if du -s $NAAM
			then
				true	#dit is een dummy commando
			else
				echo "Waarschuwing: u mag (delen van) $NAAM niet lezen"
			fi
		else
			echo "Sorry, $NAAM is geen directory"
		fi
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	13)	echo $CLR
		echo 'Geef de naam van de directory: \c'
		read NAAM
		if test -d "$NAAM" 2>/dev/null
		then
			echo "${BOLD}UNIX-commando: du $NAAM | sort -nr ${NORMAL}"
			echo
			echo "BLOKKEN 	NAAM"
			du $NAAM | sort -nr | pg
		else
			echo "Sorry, $NAAM is geen directory"
		fi
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	21)	echo $CLR
		echo "${BOLD}UNIX-commando: who ${NORMAL}"
		who
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	22) 	echo $CLR
		echo "${BOLD}UNIX-commando: ps -u ${LOGNAME} ${NORMAL}"
		echo
		ps -u ${LOGNAME}
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	23)	echo $CLR
		echo "${BOLD}UNIX-commando: ps -ef ${NORMAL}"
		echo
		ps -ef
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	24)	echo $CLR
		echo "Sammenvatting info huidige processen:"
		ps -u ${LOGNAME} | sed -e 's/  */ /g' -e 's/^ //' |
			cut -d' ' -f1 | tail +2 | pr -3 -t -w80
		SIG=""
		while [ "$SIG" != 15 -a "$SIG" != 9 ]
		do
			echo "Waarschuwing (w) of stop-signaam (s) sturen: \c"
			read answers
			case "$answers" in 
			w) SIG=15
				;;
			s) SIG=9
				;;
			*) echo "Foute keuze: geef 'w' of 's'"
				;;
			esac
		done
		echo "Geef process-nummer(s): \c"
		read NUMMERS
		echo 
		echo "${BOLD}UNIX-commando: kill -$SIG $NUMMERS ${NORMAL}"
		if kill -$SIG $NUMMERS 2>/dev/null
		then
			echo "signaal verstuurd naar $NUMMERS"
		else
			echo "u kunt geen signaal sturen naar een of meerdere"
			echo "processen uit: $NUMMERS"
		fi
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	90)	echo $CLR
		echo 'Geef de naam van de file die u wilt editen: \c'
		read NAAM
		echo "${BOLD}UNIX-commando: vi $NAAM ${NORMAL}"
		echo "Zie VI-handleiding over gebruik van editor"
		sleep 2
		vi $NAAM
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	91)	echo $CLR
		echo 'In de UNIX shell kunt u rechtstreeks met de UNIX-commandos werken'
		sh
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	99)
		echo Tot ziens
		exit
		;;
	!*)	COMM=`expr "$KEUZE" : '!\(.*\)'`
		echo $CLR
		echo "${BOLD}UNIX-commando: $COMM ${NORMAL}"
		echo "$COMM"
		echo 'Geef <RETURN> om verder te gaanA ; read answ'
		;;
	*)	echo $CLR
		echo 'Ongeldige keuze (nummer of !<UNIX-commando> geven!)'
		echo 'Geef <RETURN> om verder te gaan' ; read answ
		;;
	esac
done 	# einde van de hoofd-loop
