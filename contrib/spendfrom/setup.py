from distutils.core import setup
setup(name='brtxspendfrom',
      version='1.0',
      description='Command-line utility for bitcoinrtx "coin control"',
      author='Gavin Andresen',
      author_email='gavin@bitcoinrtxfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
