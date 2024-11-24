import gzip
import io

f = open("html.txt", "r")
content = f.read()

# Compress the string using gzip
compressed_data = io.BytesIO()
with gzip.GzipFile(fileobj=compressed_data, mode='wb') as f:
    f.write(content.encode('utf-8'))

# Get the compressed byte sequence
compressed_bytes = compressed_data.getvalue()

# Print out the compressed data in C-style byte array format
for i, byte in enumerate(compressed_bytes):
  if i % 30 == 0:
      print("\n", end="")
  print(f"{byte},", end="")
