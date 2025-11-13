ARQUIVOS=("pequeno.txt" "grande100.txt")
THREADS=(1 2 4 8)
EXEC="./eachrink"

# Cria pasta de resultados
mkdir -p resultados

for ARQ in "${ARQUIVOS[@]}"; do
  SAIDA_COMPACTADA="${ARQ%.txt}_teste.chrinked"
  SAIDA_FINAL="${ARQ%.txt}_teste.txt"
  ARQ_RESULTADOS="resultados/resultados_${ARQ%.txt}.txt"
  
  echo "=== Testes para $ARQ ===" > "$ARQ_RESULTADOS"
  echo "" >> "$ARQ_RESULTADOS"

  for T in "${THREADS[@]}"; do
    echo "Compactando $ARQ com $T threads..."
    echo "Threads: $T" >> "$ARQ_RESULTADOS"
    for i in {1..5}; do
      { time $EXEC c "$ARQ" "$SAIDA_COMPACTADA" $T ; } 2>&1 | grep real >> "$ARQ_RESULTADOS"
    done
    echo "" >> "$ARQ_RESULTADOS"

    echo "Descompactando $SAIDA_COMPACTADA com $T threads..."
    echo "Threads: $T (descompactacao)" >> "$ARQ_RESULTADOS"
    for i in {1..5}; do
      { time $EXEC d "$SAIDA_COMPACTADA" "$SAIDA_FINAL" $T ; } 2>&1 | grep real >> "$ARQ_RESULTADOS"
    done
    echo "" >> "$ARQ_RESULTADOS"
  done
done

echo "---------------------------------------"
echo "Testes finalizados! Resultados salvos em ./resultados/"
