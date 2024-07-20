import re

texto = 'Meu e-mail e exemplo@gmail.com e voce pode me contatar em outro_email@yahoo.com.'

resultado = len(re.findall('@', texto))
print("O caractere '@' apareceu", resultado, "vezes no texto")

resultado = re.findall(r'voce (\w+)', texto)
print("A palavra apos 'voce' e:", resultado[0])

emails = re.findall(r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-z|a-z]{2,}\b', texto)
print(emails)

text = "O aluno estava incrivelmente perdido, mas encontrou a DSA e rapidamente comecou a aprender"
for m in re.finditer(r"\w+mente\b", text):
    print('%02d-%02d: %s' % (m.start(), m.end(), m.group(0)))
