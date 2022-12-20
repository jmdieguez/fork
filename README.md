# Lab - Fork

Repositorio para el esqueleto del [lab fork](https://fisop.github.io/7508/lab/fork) del curso Mendez-Fresia de **Sistemas Operativos (7508) - FIUBA**

## Compilar

```bash
$ make
```

## Linter

```bash
$ make format
```

# Desafíos

Los desafíos que decidieron implementarse son: ps (5pts) y timeout (5pts).

## ps0

### Enunciado

El comando process status muestra información básica de los procesos que están corriendo en el sistema. Se pide como mínimo una implementación que muestre el pid y comando (i.e. argv) de cada proceso. Esto es equivalente a hacer:
  
    $ ps -eo pid,comm

Toda esta información se obtiene del pseudo-filesystem /proc, que mantiene acceso de sólo lectura a muchas estructuras de control del kernel relacionadas con procesos. En particular, los datos de cada proceso se encuentran en el subdirectorio /proc/[pid], siendo pid el process ID del proceso.

### Resolución

Entre los diversos grupos de archivos y directorios contenidos por el pseudo-filesystem /proc, para llevar a cabo esta mínima implementación de ps los que nos interesa son:

  * Los subdirectorios /proc/[pid] que refieren a la información correspondiente a cada proceso en ejecución, identificando a cada uno justamente por su process ID.

  * El archivo /proc/[pid]/comm que contiene el nombre del comando asociado a dicho proceso.

![Fig. 1](https://blog2opstree.files.wordpress.com/2021/08/lsof2.png?w=1024)

El programa ps0.c en resumidas cuentas lo que hace es:

  * Abrir el directorio /proc/.
  * Lee todas las entradas dentro del directorio.
  * Toma aquellas cuyo nombre es numérico, ignorando al resto (ya que no se refieren a información de procesos). -> /proc/[pid]
  * Lee el archivo "comm" contenido en dicho directorio.
  * Por cada una de estas entradas imprime: [pid - comm].

### Salida esperada:

```
manu@manu:~/Desktop/sisop_2022b_dieguez/shell$ ps -eo pid,comm
    PID COMMAND
      1 systemd
      2 kthreadd
      3 rcu_gp
      4 rcu_par_gp
      5 netns
      7 kworker/0:0H-events_highpri
      9 kworker/0:1H-events_highpri
      
[...]

  33677 kworker/0:1-events
  33703 kworker/1:0-events
  33737 kworker/u8:3-flush-8:0
  33738 kworker/3:0-events
  33739 kworker/0:0-events
  33744 kworker/2:1-events
  33781 ps
```

### Salida obtenida

```
manu@manu:~/Desktop/sisop_2022b_dieguez/fork$ ./ps0
    PID COMMAND
      1 systemd
      2 kthreadd
      3 rcu_gp
      4 rcu_par_gp
      5 netns
      7 kworker/0:0H-events_highpri
      9 kworker/0:1H-events_highpri
     10 mm_percpu_wq
     11 rcu_tasks_rude_
     12 rcu_tasks_trace
     13 ksoftirqd/0
     14 rcu_sched
     15 migration/0
     16 idle_inject/0
     18 cpuhp/0
     19 cpuhp/1
     20 idle_inject/1
     21 migration/1
     22 ksoftirqd/1
     24 kworker/1:0H-events_highpri
     25 cpuhp/2
     26 idle_inject/2
     27 migration/2
     28 ksoftirqd/2
     30 kworker/2:0H-events_highpri
     31 cpuhp/3
     32 idle_inject/3
     33 migration/3
     34 ksoftirqd/3
     36 kworker/3:0H-events_highpri
     37 kdevtmpfs
     38 inet_frag_wq
     39 kauditd
     40 khungtaskd
     41 oom_reaper
     42 writeback
     43 kcompactd0
     44 ksmd
     45 khugepaged
     92 kintegrityd
     93 kblockd
     94 blkcg_punt_bio
     96 tpm_dev_wq
     97 ata_sff
     98 md
     99 edac-poller
    100 devfreq_wq
    102 watchdogd
    104 kswapd0
    105 ecryptfs-kthrea
    107 kthrotld
    108 irq/122-aerdrv
    109 irq/123-aerdrv
    110 irq/124-aerdrv
    112 acpi_thermal_pm
    114 vfio-irqfd-clea
    115 kworker/2:1H-events_highpri
    116 kworker/3:1H-events_highpri
    118 mld
    119 ipv6_addrconf
    129 kstrp
    132 zswap-shrink
    133 kworker/u9:0-hci0
    141 charger_manager
    163 kworker/1:1H-events_highpri
    191 nvme-wq
    193 nvme-reset-wq
    194 nvme-delete-wq
    197 scsi_eh_0
    198 scsi_tmf_0
    199 scsi_eh_1
    200 scsi_tmf_1
    205 irq/134-SYNA7DB
    227 jbd2/sda5-8
    228 ext4-rsv-conver
    268 systemd-journal
    299 systemd-udevd
    301 ipmi-msghandler
    372 irq/135-mei_me
    388 kworker/u9:1-i915_flip
    395 cfg80211
    425 cryptd
    457 card0-crtc0
    458 card0-crtc1
    459 card0-crtc2
    468 ath10k_wq
    469 ath10k_aux_wq
    470 ath10k_tx_compl
    653 systemd-oomd
    654 systemd-resolve
    655 systemd-timesyn
    697 accounts-daemon
    698 acpid
    701 avahi-daemon
    702 bluetoothd
    704 cron
    705 dbus-daemon
    706 NetworkManager
    712 irqbalance
    714 networkd-dispat
    715 polkitd
    716 power-profiles-
    719 rsyslogd
    721 snapd
    722 switcheroo-cont
    723 systemd-logind
    725 thermald
    729 udisksd
    730 wpa_supplicant
    735 avahi-daemon
    786 ModemManager
    815 containerd
    843 unattended-upgr
    847 gdm3
    890 cupsd
    925 rtkit-daemon
   1024 upowerd
   1102 packagekitd
   1220 colord
   1461 cups-browsed
   1462 dockerd
   1465 kerneloops
   1468 kerneloops
   1687 gdm-session-wor
   1745 systemd
   1746 (sd-pam)
   1752 pipewire
   1753 pipewire-media-
   1754 pulseaudio
   1765 gnome-keyring-d
   1767 dbus-daemon
   1781 gvfsd
   1791 gvfsd-fuse
   1793 xdg-document-po
   1803 xdg-permission-
   1809 fusermount3
   1829 tracker-miner-f
   1834 krfcommd
   1838 gdm-x-session
   1840 Xorg
   1845 gvfs-udisks2-vo
   1851 gvfs-gphoto2-vo
   1855 gvfs-afc-volume
   1860 gvfs-goa-volume
   1864 goa-daemon
   1872 goa-identity-se
   1883 gvfs-mtp-volume
   1943 gnome-session-b
   2044 at-spi-bus-laun
   2050 dbus-daemon
   2062 gnome-session-c
   2074 gnome-session-b
   2098 gnome-shell
   2125 gnome-shell-cal
   2131 evolution-sourc
   2138 dconf-service
   2141 gvfsd-metadata
   2150 evolution-calen
   2164 evolution-addre
   2184 gvfsd-trash
   2194 gjs
   2196 at-spi2-registr
   2213 xdg-desktop-por
   2217 xdg-desktop-por
   2283 sh
   2285 ibus-daemon
   2286 gsd-a11y-settin
   2288 gsd-color
   2289 gsd-datetime
   2291 gsd-housekeepin
   2293 gsd-keyboard
   2294 gsd-media-keys
   2296 gsd-power
   2297 gsd-print-notif
   2298 gsd-rfkill
   2300 gsd-screensaver
   2302 gsd-sharing
   2306 gsd-smartcard
   2307 gsd-sound
   2318 gsd-wacom
   2321 gsd-xsettings
   2359 gsd-printer
   2362 evolution-alarm
   2366 gsd-disk-utilit
   2393 snapd-desktop-i
   2427 ibus-dconf
   2428 ibus-extension-
   2445 snap-store
   2449 ibus-x11
   2459 ibus-portal
   2543 gjs
   2594 xdg-desktop-por
   2626 ibus-engine-sim
   3421 firefox
   3572 Socket Process
   3594 Privileged Cont
   3626 snap
   3915 WebExtensions
   4099 Isolated Web Co
   4161 update-notifier
   5006 Discord
   5010 Discord
   5011 Discord
   5013 Discord
   5041 Discord
   5050 Discord
   5094 Discord
   5126 Discord
   5532 RDD Process
   5534 Utility Process
   6058 ssh-agent
   6204 java
   6283 fsnotifier
   6548 jcef_helper
   6549 jcef_helper
   6560 jcef_helper
   6586 jcef_helper
   6587 jcef_helper
  18883 gnome-terminal-
  18905 bash
  30687 Isolated Web Co
  31005 gvfsd-http
  31328 kworker/u8:0-events_power_efficient
  31400 gjs
  32216 Isolated Web Co
  32324 Isolated Servic
  32445 Isolated Web Co
  32777 Isolated Web Co
  32820 Isolated Web Co
  33067 kworker/u8:2-events_unbound
  33116 gvfsd-network
  33130 gvfsd-dnssd
  33260 jcef_helper
  33307 ion.clangd.main
  33362 kworker/0:2-events
  33526 Web Content
  33530 Web Content
  33590 Web Content
  33636 kworker/1:2-events
  33674 kworker/2:0-events
  33676 kworker/3:1-events
  33703 kworker/1:0-events
  33737 kworker/u8:3-events_unbound
  33738 kworker/3:0-events
  33739 kworker/0:0-events
  33744 kworker/2:1-mm_percpu_wq
  33786 kworker/1:1-events
  33795 kworker/3:2-events
  33797 kworker/0:1-events
  33801 kworker/2:2-events
  33825 ps0
```

## timeout

### Enunciado

El comando timeout realiza una ejecución de un segundo proceso, y espera una cantidad de tiempo prefijada (e.g. timeout duración comando. Si se excede ese tiempo y el proceso sigue en ejecución, lo termina enviándole SIGTERM. Se pide implementar una versión simplificada del comando timeout. La implementación debe usar señales.

### Resolución

El programa se ejecuta de la siguiente forma:
```
  ./timeout <secs> <cmd>
```
Siendo:
  * timeout: argv[0]
  * secs:    argv[1]
  * cmd:     argv[2] en adelante
  
Una vez parseados los argumentos, se realizan los siguientes pasos:

  * Se hace fork.
  * El proceso hijo ejecuta.
  * El proceso padre inicializa un timer, con ayuda de la siguiente función:
  
```
timer_t timerid;
struct itimerspec timer = { 0 };

void
initialize_timer(int n_secs)
{
	timer.it_value.tv_sec = n_secs;     // Se establece el tiempo = secs (argv[1])

	struct sigevent sigev;

	sigev.sigev_notify = SIGEV_SIGNAL;  // En caso de que se cumpla el timer, la notificación será una señal
	sigev.sigev_signo = SIGTERM;        // El número de señal es SIGTERM

	if (timer_create(CLOCK_REALTIME, &sigev, &timerid) == ERROR ||
	    timer_settime(timerid, 0, &timer, (struct itimerspec *) NULL) == ERROR)
		exit(1);
}                                     // Se crea el timer. En caso de error el programa termina con código de salida = 1
```
  * Finalmente, el proceso padre espera a que termine el hijo.

### Comportamiento esperado:

```
manu@manu:~/Desktop/sisop_2022b_dieguez/fork$ timeout 5 echo hola
hola
manu@manu:~/Desktop/sisop_2022b_dieguez/fork$ timeout 5 sleep 10
manu@manu:~/Desktop/sisop_2022b_dieguez/fork$ 
```

### Comportamiento observado en la implementación:

```
manu@manu:~/Desktop/sisop_2022b_dieguez/fork$ ./timeout 5 echo hola
hola
manu@manu:~/Desktop/sisop_2022b_dieguez/fork$ ./timeout 5 sleep 10
Terminated
```

El programa efectivamente termina la ejecución del programa al momento de que se cumpla el timer, incluso imprime por pantalla "Terminated", a diferencia de el timeout tradicional.
