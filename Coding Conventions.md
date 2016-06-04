Tabs should be used instead of spaces. For alignment, use a visual tab size of 4.
This project uses the ANSI formatting specifications with the exception that empty brackets don't need a newline and can be like the following: `{ }`.

Functions, references and pointers are written like `int *a;` and `int &b` since `int& c1, c2;` would be misleading (c2 is not a reference). Here is some demo code:

```
int function(int *ptr, char &ref)
{
	int i;
	for (i = 0; i < 23 && getBool(); ++i) { }
	switch(ref)
	{
	case 'a':
		return 1;
	case 'b':
		i = 2;
		break;
	case 'c':
		{
			int a = 2;
			while (getBool())
				++a;
			i = a;
		}
		break;
	default:
		return 0;
	}
	return i;
}
```

Note that if a loop is used without content as shown above, `{ }` is preferred over a semicolon since it highlights that this was done intentionally.

# Things to remember

Never implement a class function in the header, even if empty. Although trivial, I've found myself adding more and more to empty constructors until I get to the point where I need to unnecessarily #include something.

Try to use a forward declaration if possible in headers rather than using #include.
