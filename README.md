# IC_G07_Proj1
### Projeto 1 da cadeira de Informação e Codificação de MECT

Parte I do projeto localizada na pasta [**sndfile-example**](sndfile-example): <br>

      1. Compilar (necessário estar no diretório ../sndfile-example/sndfile-example-src) 
         * make

      2. Testar (necessário estar no diretório ../sndfile-example/sndfile-example-src/) 
         * ../sndfile-example-bin/wav_hist sample.wav 0                       -> testar WAVHist #1
         * gnuplot: plot "MID_channel.txt" with boxes                         -> testar WAVHist #2
         * gnuplot: plot "SIDE_channel.txt" with boxes                        -> testar WAVHist #3
         * ../sndfile-example-bin/wav_quant sample.wav 13 output.wav          -> testar wav_quant
         * ../sndfile-example-bin/wav_cmp sample.wav output.wav               -> testar wav_cmp
         * ../sndfile-example-bin/wav_effects sample.wav out.wav single-echo  -> testar wav_effects
  <br>

Parte II do projeto localizada na pasta [**Part_II**](Part_II): <br>
    
    Exercicio 6 - BitStream:
      1. Compilar (necessário estar no diretório ../Part_II/exe6) 
         * g++ BitStream.cpp

      2. Testar (necessário estar no diretório ../Part_II/exe6/test_programs) 
         * ./singleBit_test  -> testar leitura/escrita de 1 bit
         * ./nBits_test      -> testar leitura/escrita de N bit
       
    Exercicio 7 - Codificador e Descodificador:
      1. Compilar (necessário estar no diretório ../Part_II/exe7) 
         * g++ encoder.cpp -o encoder   -> compilar codificador (é necessario mover executavel para /test_programs)
         * g++ decoder.cpp -o decoder   -> compilar descodificador (é necessario mover executavel para /test_programs)

      2. Testar (necessário estar no diretório ../Part_II/exe7/test_programs) 
         * ./encoder teste.txt    -> testar codificador
         * ./decoder encodedFile  -> testar descodificador (necessário testar codificador primeiro, de modo a criar o ficheiro binario)
  <br>
  
Part III do projeto localizada na pasta [**Part_III**](Part_III) contém a implementação do Codec e pasta com ficheiros de teste: <br>

    1. Compilar (necessário estar no diretório ../Part_III) 
       * g++ Codec.cpp -lsndfile

    2. Testar (necessário estar no diretório ../Part_III/test_programs) 
       * ./test
       
  <br>
   
Part IV do projeto contida no relatório [**IC_G07_Proj1.pdf**](IC_G07_Proj1.pdf) 

