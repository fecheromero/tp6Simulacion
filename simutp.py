import sys
import random

cantidad_llegadas = 0
cantidad_cajeros = 1
cantidad_envolvedores = 2
cola_envoltura = 0
cola_cobro = 0
tiempo_de_proxima_llegada = 0
tiempo_de_proximas_salidas_envolturas = []
tiempos_de_proximas_salidas_cobro = []
tiempo = 0
sumatoria_tiempos_espera_envoltura = 0
sumatoria_tiempos_espera_cobro = 0
sumatoria_tiempos_de_envoltura = 0
sumatoria_tiempos_de_cobro = 0
ultimo_calculo_envoltura = 0
ultimo_calculo_cobro = 0
total_de_personas = 0
tiempo_final = 10000
vaciando = False


def condiciones_iniciales():
    for i in range(cantidad_envolvedores):
        tiempo_de_proximas_salidas_envolturas.append(sys.maxsize)
    for i in range(cantidad_cajeros):
        tiempos_de_proximas_salidas_cobro.append(sys.maxsize)


def generar_intervalo_llegada():
    while (True):
        R1 = random.random()
        R2 = random.random()
        xi = 6 * R1
        yi = 3 * R2
        f_xi = ((-3 / 32) * pow(xi, 2)) + ((3 / 8) * xi)
        if (yi <= f_xi): return xi


def generar_tiempo_envoltura():
    R = random.random()
    return 2*R +1


def generar_tiempo_cobro():
    while (True):
        R1 = random.random()
        R2 = random.random()
        xi = 2 + 2*R1
        yi = (2/3) * R2
        f_xi = (1/6)*xi
        if (yi <= f_xi): return xi

def llegada():
    global tiempo
    global tiempo_de_proxima_llegada
    global cantidad_llegadas
    global cola_envoltura
    global sumatoria_tiempos_de_envoltura
    global sumatoria_tiempos_espera_envoltura
    global ultimo_calculo_envoltura

    tiempo = tiempo_de_proxima_llegada
    print('Llegada en ' + str(tiempo))
    intervalo = generar_intervalo_llegada()
    tiempo_de_proxima_llegada += intervalo
    cantidad_llegadas += 1
    if (cola_envoltura > cantidad_envolvedores):
        sumatoria_tiempos_espera_envoltura += (tiempo - ultimo_calculo_envoltura) * (cola_envoltura - cantidad_envolvedores)
    ultimo_calculo_envoltura = tiempo
    cola_envoltura += 1
    if (cola_envoltura <= cantidad_envolvedores):
        tiempo_envoltura = generar_tiempo_envoltura()
        sumatoria_tiempos_de_envoltura += tiempo_envoltura
        tiempo_de_proximas_salidas_envolturas.remove(max(tiempo_de_proximas_salidas_envolturas))
        tiempo_de_proximas_salidas_envolturas.append(tiempo + tiempo_envoltura)


def envoltura():
    global ultimo_calculo_envoltura
    global cola_cobro
    global sumatoria_tiempos_espera_cobro
    global ultimo_calculo_cobro
    global sumatoria_tiempos_de_cobro
    global cola_envoltura
    global sumatoria_tiempos_espera_envoltura
    global sumatoria_tiempos_de_envoltura
    global tiempo

    tiempo = proxima_salida_envoltura
    print('Envoltura en ' + str(tiempo))
    if (cola_envoltura > cantidad_envolvedores):
        sumatoria_tiempos_espera_envoltura += (tiempo - ultimo_calculo_envoltura) * (cola_envoltura - cantidad_envolvedores)
    ultimo_calculo_envoltura = tiempo
    cola_envoltura -= 1
    if (cola_cobro > cantidad_cajeros):
        sumatoria_tiempos_espera_cobro += (tiempo - ultimo_calculo_cobro) * (cola_cobro - cantidad_cajeros)
    ultimo_calculo_cobro = tiempo
    cola_cobro += 1
    tiempo_de_proximas_salidas_envolturas.remove(proxima_salida_envoltura)
    tiempo_de_proximas_salidas_envolturas.append(sys.maxsize)
    if (cola_envoltura >= cantidad_envolvedores):
        tiempo_envoltura = generar_tiempo_envoltura()
        sumatoria_tiempos_de_envoltura += tiempo_envoltura
        tiempo_de_proximas_salidas_envolturas.remove(max(tiempo_de_proximas_salidas_envolturas))
        tiempo_de_proximas_salidas_envolturas.append(tiempo + tiempo_envoltura)
    if (cola_cobro <= cantidad_cajeros):
        tiempo_cobro = generar_tiempo_cobro()
        sumatoria_tiempos_de_cobro += tiempo_cobro
        tiempos_de_proximas_salidas_cobro.remove(max(tiempos_de_proximas_salidas_cobro))
        tiempos_de_proximas_salidas_cobro.append(tiempo + tiempo_cobro)


def salida_cobro():
    global ultimo_calculo_cobro
    global cola_cobro
    global sumatoria_tiempos_de_cobro
    global sumatoria_tiempos_espera_cobro
    global tiempo

    tiempo = proxima_salida_cobro
    print('Cobro en ' + str(tiempo))
    if (cola_cobro > cantidad_cajeros):
        sumatoria_tiempos_espera_cobro += (tiempo - ultimo_calculo_cobro) * (cola_cobro - cantidad_cajeros)
    ultimo_calculo_cobro = tiempo
    cola_cobro -= 1
    tiempos_de_proximas_salidas_cobro.remove(proxima_salida_cobro)
    tiempos_de_proximas_salidas_cobro.append(sys.maxsize)
    if (cola_cobro >= cantidad_cajeros):
        tiempo_cobro = generar_tiempo_cobro()
        sumatoria_tiempos_de_cobro += tiempo_cobro
        tiempos_de_proximas_salidas_cobro.remove(max(tiempos_de_proximas_salidas_cobro))
        tiempos_de_proximas_salidas_cobro.append(tiempo + tiempo_cobro)


def imprimir_resultados():
    print('Para ' + str(cantidad_envolvedores) + ' envolvedores y ' + str(cantidad_cajeros) + ' cajeros')
    porcentaje_tiempo_ocioso_cobro = (1 - (sumatoria_tiempos_de_cobro / cantidad_cajeros) / tiempo) * 100
    porcentaje_tiempo_ocioso_envoltura = (1 - (sumatoria_tiempos_de_envoltura / cantidad_envolvedores) / tiempo) * 100
    promedio_espera_envoltura = sumatoria_tiempos_espera_envoltura / cantidad_llegadas
    promedio_espera_cobro = sumatoria_tiempos_espera_cobro / cantidad_llegadas
    print('Porcentaje de tiempo ocioso en el cobro: ' + str(porcentaje_tiempo_ocioso_cobro) + '%')
    print('Porcentaje de tiempo ocioso en la envoltura: ' + str(porcentaje_tiempo_ocioso_envoltura) + '%')
    print('Promedio de tiempo de espera en envoltura: ' + str(promedio_espera_envoltura))
    print('Promedio de tiempo de espera en cobro: ' + str(promedio_espera_cobro))


# simulacion
condiciones_iniciales()
while (True):
    proxima_salida_envoltura = min(tiempo_de_proximas_salidas_envolturas)
    proxima_salida_cobro = min(tiempos_de_proximas_salidas_cobro)
    index_proxima_envoltura = tiempo_de_proximas_salidas_envolturas.index(proxima_salida_envoltura)
    index_proxima_salida = tiempos_de_proximas_salidas_cobro.index(proxima_salida_cobro)
    if (tiempo_de_proxima_llegada <= proxima_salida_envoltura and tiempo_de_proxima_llegada <= proxima_salida_cobro):
        llegada()
    elif (proxima_salida_envoltura <= proxima_salida_cobro):
        envoltura()
    else:
        salida_cobro()
    if (tiempo <= tiempo_final): continue
    if (cola_envoltura + cola_cobro > 0):
        if (not vaciando):
            tiempo_de_proxima_llegada = sys.maxsize
            vaciando = True
        continue
    break
imprimir_resultados()
