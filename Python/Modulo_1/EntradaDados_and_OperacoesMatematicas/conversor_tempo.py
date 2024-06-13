segundos=int(input("Por favor, entre com o número de segundos que deseja converter: "))

dias=segundos//86400
segundos_rest1=segundos%86400
horas=segundos_rest1//3600
segundos_rest2=segundos_rest1%3600
minutos=segundos_rest2//60
segundos_final=segundos_rest2%60

print(dias,"dias,",horas,"horas,",minutos,"minutos e",segundos_final,"segundos.")