# Intermediate Language file format

```yaml
version: 1
main: 0
types:
  - name: MainClass
    base: BaseClass # Omission means no base class
    fields:
      - int
    methods:
      - name: Main
        returns: null # Omission equivalent to null, void
        params: # Omission equivalent to no parameters
          - int
          - MainClass
        locals: # Omission equivalent to no local variables
          - char
          - bool
        code: # Omission equivalent to empty code block
          - ldc_str: "My String comes here"
          - ret
```

Above is a sample code for the format of the intermediate language. The types can be either a class or an array.  The code can have values of either types int, char, string, bool.
