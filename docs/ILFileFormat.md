# Intermediate Language file format

```yaml
version: 1
main: 0
types:
  - Class:
    name: MainClass
    base: # Here index of base class (e.g. 1)
    fields:
      - -1
    methods:
      - Main
        returns: null
        params:
          - -1
          - 1
        locals:
          - -2
          - 3
        code:
          - ldc_str: "My String comes here"
          - ret
  - Array:
    length: 3
```

Above is a sample code for the format of the intermediate language. The types can be either a class or an array.  The code can have values of either types int, char, string, bool.
