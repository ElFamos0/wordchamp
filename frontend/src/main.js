import { createApp } from 'vue'
import { createStore } from 'vuex'
import auth from '@/api/store'
import App from '@/App.vue'
import router from './router' 
import BootstrapVue3 from 'bootstrap-vue-3'
import 'bootstrap/dist/css/bootstrap.css'
import 'bootstrap-vue-3/dist/bootstrap-vue-3.css'

// Create a new store instance.
const store = createStore({
  modules: {
    auth
  }
})

createApp(App).use(BootstrapVue3).use(router).use(store).mount('#app')