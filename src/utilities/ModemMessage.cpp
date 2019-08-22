// Copyright (c) 2018 LooUQ Inc. All rights reserved.

// Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include "ModemMessage.h"
#include "Utilities.h"



#include <string.h>


using namespace iotq;
using namespace iotq::devices::modems;




/**
 *  @brief Constructor.
 */
iotq::devices::modems::ModemMessage::ModemMessage()
{

}



/**
 *  @brief Destructor.
 */
iotq::devices::modems::ModemMessage::~ModemMessage()
{
	Dispose(m_FullMessage);
}



void iotq::devices::modems::ModemMessage::InvalidateMessage()
{
	Invalidate(m_FullMessage);
	m_MessageSize = NULL;
	m_Tokens.Clear();
}



/**
 *  @brief Tokenize by defined delimiter(s)
 *
 *	@param delimiter_s Delimiter(s) by which to tokenize the message
 */
void iotq::devices::modems::ModemMessage::TokenizeBy(const char* delimiter_s)
{
	if (m_Tokenized) return;
	m_MessageSize = strlen(m_FullMessage);
	char* line_begin = strtok(m_FullMessage, delimiter_s);
	while (line_begin)
	{
		m_Tokens.PushBack(line_begin);
		line_begin = strtok(NULL, delimiter_s);
	}
	m_Tokenized = true;
}



/**
 *  @brief Detokenize the message.
 *
 *	Upon tokenizing a message, the delimiter(s) are replaced with
 *		null-characters to distinguish each token. The message must
 *		then be detokenized with a substitute character for
 *		the full message.
 *
 *	@param subCh The character to sub in for the null-characters
 */
void iotq::devices::modems::ModemMessage::Detokenize(char subCh)
{
	if (!m_Tokenized) return;
	snrepl_strchr(m_FullMessage, '\0', subCh, m_MessageSize);
	m_Tokenized = false;
}



/**
 *  @brief Look for, or part of, a token with the given substring.
 *
 *	@param subToken The token, or part of one, to look for
 */
bool iotq::devices::modems::ModemMessage::LookFor(const char* subToken)
{
	bool result = false;

	size_t et_size = strlen(subToken);
	size_t tokIndex = 0;
	for (const char* token : m_Tokens)
	{
		if (!strncmp(subToken, token, et_size))
		{
			m_ActualExpression = tokIndex;
			result = true;
			break;
		}
		tokIndex++;
	}

	return result;
}



void iotq::devices::modems::ModemMessage::Reserve(size_t reserveLen)
{
	m_FullMessage = new char[reserveLen];
	memset(m_FullMessage, 0x00, reserveLen);
}


const char* iotq::devices::modems::ModemMessage::operator[](size_t line)
{
	return m_Tokens.At(line);
}




/**
 *  @brief Get the actual expression that matched the sub-token.
 *
 *	@return A string pointer to the matched expression in the message
 */
const char* iotq::devices::modems::ModemMessage::GetActualExpression()
{
	return m_Tokens[m_ActualExpression];
}



const char * iotq::devices::modems::ModemMessage::GetNextExpression()
{
	return m_Tokens[m_ActualExpression+1];
}



/**
 *  @brief Get the last token.
 *
 *	@return A string pointer to the last token.
 */
const char* iotq::devices::modems::ModemMessage::GetLastToken()
{
	if (m_Tokens.Back() == nullptr)
		return NULL;

	return m_Tokens.Back();
}



size_t iotq::devices::modems::ModemMessage::GetNumOfTokens()
{
	return m_Tokens.GetSize();
}



/**
 *  @brief Get the full message.
 *
 *	This method hands off the underlying data to the provided handle.
 *		If 'Detokenize' was not called prior to this call, the data will
 *		appear to be early-terminated. However, the returned size will
 *		reflect the true length of the data.
 *
 *	@param message A handle to handoff the message to
 *	@return The size of the message
 */
size_t iotq::devices::modems::ModemMessage::GetFullMessage(char* message[])
{
	*message = m_FullMessage;
	Invalidate(m_FullMessage);
	return m_MessageSize;
}



/**
 *  @brief Set the full message of this object.
 *
 *	The object is simply a contianer, so this method is the initializing
 *		method by which it provides this object with data to work on.
 *
 *	@param message The message handle to accept data from
 *	@param msgSz The size of the message being provided by the handle.
 */
void iotq::devices::modems::ModemMessage::SetFullMessage(char* message[], size_t msgSz)
{
	m_FullMessage = *message;
	m_MessageSize = msgSz;
}



/**
 *  @brief Get a cstring reference to the underlying data.
 */
const char* iotq::devices::modems::ModemMessage::c_str() const
{
	return m_FullMessage;
}
