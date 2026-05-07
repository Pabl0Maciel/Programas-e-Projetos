"""
Módulo utilitário para configuração de logging.

Este arquivo fornece uma função reutilizável para criar e configurar 
loggers da aplicação, permitindo registrar mensagens tanto no console 
quanto em arquivo, com formatação padronizada.
"""

#################################################################################################################
###                                                BIBLIOTECAS                                                ###
#################################################################################################################
import logging
from pathlib import Path

#################################################################################################################
###                                             CONFIGURACAO DO LOGGER                                        ###
#################################################################################################################
def setup_logger(log_file: Path, name: str = "app_logger") -> logging.Logger:
    """
    Configura e retorna um logger com saída para console e arquivo.

    Args:
        log_file (Path): Caminho do arquivo de log.
        name (str, opcional): Nome identificador do logger. 
            Padrão: "app_logger".

    Returns:
        logging.Logger: Logger configurado.
    """

    # Configuração do logger
    logger = logging.getLogger(name)
    logger.setLevel(logging.INFO)
    logger.handlers.clear()

    # Formatação das mensagens de log
    formatter = logging.Formatter(
        fmt="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S"
    )

    # Configuração do handler de console
    console_handler = logging.StreamHandler()
    console_handler.setLevel(logging.INFO)
    console_handler.setFormatter(formatter)

    # Configuração do handler de arquivo
    file_handler = logging.FileHandler(log_file, encoding="utf-8")
    file_handler.setLevel(logging.INFO)
    file_handler.setFormatter(formatter)

    # Adiciona os handlers ao logger
    logger.addHandler(console_handler)
    logger.addHandler(file_handler)
    logger.propagate = False
    return logger
#################################################################################################################