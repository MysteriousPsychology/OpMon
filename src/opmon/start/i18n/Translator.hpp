/*!
 * \file Translator.hpp
 * \author BAKfr
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <map>
#include <string>
#include <unordered_set>

namespace OpMon {
    namespace I18n {

        class ATranslatable;

        /*!
         * \class Translator Translator.hpp "start/opmon/i18n/Translator.hpp"
         * \brief Class in charge of the lang setting. It load (and reload) language file.
         *
         * When the lang changes, it informs all Translatable instances registered with subscribe().
         *
         * \note This class is a singleton. It can only be acceded by using getInstance().
         */
        class Translator {
          public:
            //Ensure Singleton can't be copied.
            Translator(Translator const &) = delete;
            void operator=(Translator const &) = delete;

            static Translator &getInstance();

            /*!
             * \brief Sets the language.
             * \warning It MUST be called at start to set the first language.
             *
             * \param lang_code should be "en", "es" or "fr".
             */
            void setLang(const std::string &lang_code);

            /*!
             * \return The current language.
             */
            const std::string &getLang();

            /*!
             * \return A map of available languages, the first element being the language code, and the second the name of the language in said language.
             */
            const std::map<const std::string, const std::string> getAvailableLanguages();

            void subscribe(ATranslatable *listener);
            void unsubscribe(ATranslatable *listener);

          private:
            Translator() = default;

            std::string _currentLang;
            std::unordered_set<ATranslatable *> _listeners;
        };

    } // namespace I18n
} // namespace OpMon
