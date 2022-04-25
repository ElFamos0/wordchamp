
import { createApp } from 'vue'
import { createStore } from 'vuex'
import auth from '@/api/store'
import App from '@/App.vue'
import router from './router' 
import BootstrapVue3 from 'bootstrap-vue-3'
import 'bootstrap/dist/css/bootstrap.css'
import 'bootstrap-vue-3/dist/bootstrap-vue-3.css'
import vuetify from './plugins/vuetify'
import { loadFonts } from './plugins/webfontloader'
import { library } from "@fortawesome/fontawesome-svg-core";
import { FontAwesomeIcon } from "@fortawesome/vue-fontawesome";

loadFonts()

//import * as icons from "@fortawesome/free-solid-svg-icons";

import { faHouse, faPlay } from "@fortawesome/free-solid-svg-icons";

library.add(faHouse)
library.add(faPlay)

const store = createStore({
  modules: {
    auth
  }
})

createApp(App)
  .use(BootstrapVue3)
  .use(router)
  .use(store)
  .use(vuetify)
  .component('font-awesome-icon', FontAwesomeIcon)
  .mount('#app')
