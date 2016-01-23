//
// Created by metopa on 5.5.15.
//

#ifndef HTTP_SERVER_CABSTRACTCONTENT_H
#define HTTP_SERVER_CABSTRACTCONTENT_H


#include <cstddef>
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

/**
 * This is abstract class that represents a content generator entity.
 * It provides a unified interface for the file loading process.
 */
class CAbstractContent {
protected:
	vector<uint8_t> data_m;
	/**< A storage that contains the generated data*/
	string userPath_m;
	/**< A resource path, that was originally requested by the client. */
	string realPath_m;
	/**< A real resource path. */
	size_t size_m;
	/**< A size of the generated data. */
	char createTime_m[32];
	/**< The data creation time. */
	char modTime_m[32]; /**< The data last modification time. */
public:
	/**
	 * Constructs content object.
	 * Initializes some private attributes.
	 *
	 * \param userPath - A resource path as requested by user.
	 * \param realPath - A resource path that refers to the real resource location on a local machine.
	 */
	CAbstractContent( const string& userPath, const string& realPath );

	/**
	 * An empty constructor.
	 */
	CAbstractContent();

	virtual ~CAbstractContent();

	/**
	 * This method load the requested resource into a virtual memory and initializes helper attributes.
	 */
	virtual void load() = 0;

	/**
	 * \return The size of the generated data.
	 */
	size_t getSize() const;

	/**
	 * \return The pointer to the NULL-terminated string that contains resource creation time.
	 */
	virtual const char * getCreateTime() const;

	/**
	 * \return The pointer to the NULL-terminated string that contains resource modification time.
	 */
	virtual const char * getModTime() const;

	/**
	 * \return The generated data.
	 */
	const vector<uint8_t>& getData() const;

protected:
	void creationTime();
};


#endif //HTTP_SERVER_CABSTRACTCONTENT_H
