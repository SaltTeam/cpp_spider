/*
** SpiderException.hpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/includes/SpiderException.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Oct 03 14:30:19 2017 Hugo SOSZYNSKI
** Last update Tue Oct 03 14:30:19 2017 Hugo SOSZYNSKI
*/

#ifndef CPP_SPIDER_SPIDEREXCEPTION_HPP
# define CPP_SPIDER_SPIDEREXCEPTION_HPP

# include <exception>
# include <string>

namespace spider
{

  class SpiderException : public std::exception
  {
  protected:
    std::string _message;

  public:
    SpiderException(std::string const &message);

    SpiderException(SpiderException const &other);

    virtual ~SpiderException() noexcept(true);

    SpiderException &operator=(SpiderException const &other);

  public:
    virtual const char *what() const noexcept(true);
  };
}

#endif /* !CPP_SPIDER_SPIDEREXCEPTION_HPP */
