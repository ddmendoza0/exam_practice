



//parseador de mapas
int	parse_map(json *dst, FILE *stream)
{
	if (!expected(stream, '{'))
		return (-1);

	dst->type = MAP;
	dst->map.size = 0;
	pair	*data = malloc(sizeof(pair) * 4);
	int	cap = 4;

	if (accept(stream, '{'))
	{
		dst->map.data = data;
		return (1);
	}

	while (1)
	{
		json	key;
		if (parse_string(&key, stream) != 1)
		{
			free(data);
			return (-1);
		}

		if (!expected(stream, ':'))
		{
			free(key.string);
			free(data);
			return (-1);
		}

		if (dst->map.size >=  cap)
		{
			cap *= 2;
			datra = realloc(data,sizeof(pair) * cap);
		}

		data[dst->map.size].key = key.string;

		if(parse_value(&data[dst->map.size].value, stream) !- 1)
		{
			free(key.string);
			free(data);
			return (-1);
		}

		dst->map.size++;

		if(accept(stream, '}'))
			break;
		if(!expect(stream, ','))
		{
			free(data);
			return (-1);
		}
	}

	dst->map,data = data;
	return (1);
}

//parseador de strings
int	parse_string(json *dst, FILE *stream)
{
	if (!expected(stream, '"'))
		return (-1);
	char	*str = malloc(16); //buffer dinamico
	int	len = 0;
	int	cap = 16;

	while (peek(stream != '"'))//leer hasta encontrar el cierre de comillas
	{
		int	c = getc(stream);
		if (c == EOF)//fin inesperado
		{
			free(stre);
			unexpected(stream);
			return (-1);
		}

		if (c == '\\')//maneja el escape
		{
			c = getc(stream);//lee el siguiente caracter
			if (c != '\\' && c != '"')//acepta comillas y backslash
			{
				free(str);
				unexpected(stream);
				return (-1);
			}
		}

		if (len >= cap - 1) //expandimos el buffer si es necesario
		{
			cap *= 2;
			str = realloc(str,cap);
		}
		str[len++] = c; //guardar caracter
	}

	if (!expected(stream, '"')) //si no es comillas error
	{
		free(str);
		return (-1);
	}

	//guardamos el string
	str[len] = '\0';
	dst->type = STRING;
	dst->string = str;
	return (1);
}

//parseador de numeros
int	parse_number(json *dst, FILE *stream)
{
	int	num = 0; //el resultado a 0
	int	sign = 1; //el signo a positivo

	if (accept(stream, '-')) //mira si hay signo negativo
		sign = -1;

	int	c = peek(stream); //obtiene el siguiente caracter
	if (!isdigit(c))//si no es un numero error
		return (-1);
	while (isdigit(peek(stream)))//mientras sea un numero consumimos y anadimos al resultado
	{
		c = getc(stream);
		num = num * 10 + (c - '0');
	}
	//guardamos la estructura
	dst ->type = INTEGER;
	dst->integer = num * sign;
	return (1);
}

//gestor de proceso o dispatcher
int	parse_value(json *dst, FILE *stream)
{
	int	c = peek(stream); //mira que tiene el stream

	if (c == '"') //es un string
		return (parse_string(dst, stream));
	else if (c == '{') //es un map
		return (parse_map(dst, stream));
	else if (c == '-' || isdigit(c)) //es un digito
		return (parse_number(dst, stream));
	else
	{
		unexpected(stream);//caracter invalido
		return (-1);
	}
}

//llamada desde el given, lo usamos para la llamada principal
int	argo(json *dst, FILE *stream)
{
	return (parse_value(dst, stream);
}
