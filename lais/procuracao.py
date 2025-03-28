template_procuracao =  """PROCURACAO 

OUTORGANTE: NOME_AUTORA 

OUTORGADO:NOME_ADV 

PODERES: Isso é um texto de teste lorem ipsun dolor sit amet 

"""

lista = [
    {"Assinante": "Alice", "Adv": "Bernardo"},
    {"Assinante": "Carla", "Adv": "Daniel"},
    {"Assinante": "Elaine", "Adv": "Fábio"}
]

lista_resultados = []

for item in lista:
    lista_resultados.append( template_procuracao.replace("NOME_AUTORA", item["Assinante"]) )

print(lista_resultados)