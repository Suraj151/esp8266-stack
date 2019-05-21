#include "DataTypeConversions.h"
#include "StringOperations.h"

int __strstr(char *str, char *substr, int _len){
	int n = 0;
	if( strlen(str) ==0 || strlen(substr) ==0 ) return -1;
	while (*str && n < _len){

		char *Begin = str;
		char *pattern = substr;

		while (*str && *pattern && *str == *pattern){
			str++; pattern++;
		}
		// if (!*pattern) return Begin;
		if (!*pattern) return n;

		str = Begin + 1;
		n++;
	}
	// return NULL;
	return -1;
}

char* __strtrim(char *str, uint16_t _overflow_limit){
	uint16_t n = 0;
	uint16_t len = strlen(str);

	if( len == 0 ) return NULL;
	while (*str && n < _overflow_limit){

		char *_begin = str;

		while ( *_begin && *_begin == ' ' && n < len && n < _overflow_limit ){
			_begin++; n++;
		}
		while ( *(str+len-1) && len > 0 && n < _overflow_limit ){
			if( *(str+len-1) == ' ' ) {*(str+len-1) = 0; n++; len--;}
			else{ break;}
		}

		return _begin;
	}
	return NULL;
}

char* __strtrim_val(char *str, char _val, uint16_t _overflow_limit){
  uint16_t n = 0;
  uint16_t len = strlen(str);

  if( len == 0 ) return NULL;
  while (*str && n < _overflow_limit){

    char *_begin = str;

    while ( *_begin && *_begin == _val && n < len && n < _overflow_limit ){
      _begin++; n++;
    }
    while ( *(str+len-1) && len > 0 && n < _overflow_limit ){
      if( *(str+len-1) == _val ) {*(str+len-1) = 0; n++; len--;}
      else{ break;}
    }

    return _begin;
  }
  return NULL;
}

bool __are_str_equals(char *str1, char *str2, uint16_t _overflow_limit ){

	int len = strlen( str1 );
	if( len != strlen( str2 ) ) return false;

	for ( int i = 0; i < len; i++ ) {

		if( str1[i] != str2[i] ) return false;
	} return true;
}

void __appendUintToBuff( char* _str, const char* _format, uint32_t _value, int _len){

	char value[20];
	memset(value, 0, 20);
	sprintf(value, (const char*)_format, _value);
	strncat(_str, value, _len);
}

void __int_ip_to_str( char* _str, uint8_t* _ip, int _len ){

	memset( _str, 0, _len );
	sprintf( _str, "%d.%d.%d.%d", _ip[0], _ip[1], _ip[2], _ip[3] );
}

void __str_ip_to_int( char* _str, uint8_t* _ip, int _len, bool _clear_str_after_done ){

	// char _buf[4];
	// memset( _buf, 0, 4 );
	_ip[0] = StringToUint8( _str, 3);
	for ( uint8_t i=0, _ip_index=1; i < strlen(_str) && i < _len; i++) {

		if( _str[i] == '.' && _ip_index < 4 ){

			_ip[_ip_index++] = StringToUint8( &_str[i+1], 3);
		}
		// if( _buf_index < 4 ) _buf[_buf_index++] = _str[i];
	}
	if( _clear_str_after_done ) memset( _str, 0, _len );
}

void __find_and_replace( char* _str, char* _find_str, char* _replace_with, int _occurence ){

  int _str_len = strlen( _str );
  int _find_str_len = strlen( _find_str );
  int _replace_str_len = strlen( _replace_with );

  int _total_len = _str_len + ( _replace_str_len * _occurence );
  char *_buf = new char[ _total_len ];
  memset( _buf, 0, _total_len );

	int j = 0, o = 0;
  for ( ;j < _str_len && o < _occurence; ) {

    int _occur_index = __strstr( &_str[j], _find_str, _str_len );
    if( _occur_index >= 0 ){

      strncat( _buf, &_str[j], _occur_index );
      strncat( _buf, _replace_with, _replace_str_len );
      j += _occur_index + _find_str_len;
      o++;
    }else{
			break;
		}
  }

	if( j<_str_len ) strncat( _buf, &_str[j], (_str_len-j) );
	int _fin_len = _str_len - ( o * _find_str_len ) + ( o * _replace_str_len );

	if( strlen( _buf ) > 0 && o > 0 ){
		memset( _str, 0, _str_len );
		memcpy( _str, _buf, _fin_len + 1);
	}
  delete[] _buf;
}

bool __get_from_json( char* _str, char* _key, char* _value, int _max_value_len ){

  int _str_len = strlen( _str );
  int _key_str_len = strlen( _key );

  char *_str_buf = new char[ _str_len ];

  memset( _str_buf, 0, _str_len );

  int _occur_index = __strstr( _str, _key, _str_len );
  if( _occur_index >= 0 ){

    int j=0;
    int no_of_commas = 0;
    int no_of_opening_curly_bracket = 0;
    int no_of_closing_curly_bracket = 0;
    int no_of_opening_square_bracket = 0;
    int no_of_closing_square_bracket = 0;


    while( j < _str_len ){

      if( _str[_occur_index+_key_str_len+j] == ',' ){
        no_of_commas++;
      }else if( _str[_occur_index+_key_str_len+j] == '{'  ){
        no_of_opening_curly_bracket++;
      }else if( _str[_occur_index+_key_str_len+j] == '}'  ){
        no_of_closing_curly_bracket++;
      }else if( _str[_occur_index+_key_str_len+j] == '['  ){
        no_of_opening_square_bracket++;
      }else if( _str[_occur_index+_key_str_len+j] == ']'  ){
        no_of_closing_square_bracket++;
      }else{

      }

      if(
        (no_of_commas > 0 && ( no_of_opening_curly_bracket +
        no_of_closing_curly_bracket + no_of_opening_square_bracket + no_of_closing_square_bracket ) == 0)
      ){
        break;
      }

      if( no_of_opening_curly_bracket > 0 &&  no_of_opening_curly_bracket == no_of_closing_curly_bracket ){
        break;
      }

      if( no_of_opening_curly_bracket == 0 && no_of_opening_square_bracket > 0 &&
          no_of_opening_square_bracket == no_of_closing_square_bracket
      ){
        break;
      }

      if( no_of_opening_curly_bracket == 0 && no_of_closing_curly_bracket > 0 &&
          no_of_opening_square_bracket == no_of_closing_square_bracket
      ){
        j--;break;
      }

      if( no_of_opening_square_bracket == 0 && no_of_closing_square_bracket > 0 &&
          no_of_opening_curly_bracket == no_of_closing_curly_bracket
      ){
        j--;break;
      }

      j++;
      delay(0);
    }

    memcpy( _str_buf, &_str[_occur_index], _key_str_len+j+1 );
    __find_and_replace( _str_buf, "\n", "", 5);
    __find_and_replace( _str_buf, _key, "", 1);
    int _key_value_seperator = __strstr( _str_buf, ":", _str_len );
    memcpy( _str_buf, _str_buf+_key_value_seperator, _key_str_len+j+1-_key_value_seperator );
    memcpy( _str_buf, __strtrim_val( _str_buf, ':', _max_value_len ), strlen(_str_buf) );
    memcpy( _str_buf, __strtrim_val( _str_buf, ',', _max_value_len ), strlen(_str_buf) );
    memcpy( _str_buf, __strtrim( _str_buf, _max_value_len ), strlen(_str_buf) );
    memcpy( _str_buf, __strtrim_val( _str_buf, '"', _max_value_len ), strlen(_str_buf) );

		memset( _value, 0, _max_value_len );
		memcpy( _value, _str_buf, strlen(_str_buf) );
  }

  delete[] _str_buf;
	return _occur_index >= 0;
}
