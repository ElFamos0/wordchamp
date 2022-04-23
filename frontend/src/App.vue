<template>
  <div id="app">
    <div id="nav">
      <b-nav tabs>
          <b-modal id="modal-profile" :title="'Profil de ' + username">
            <Profile />
          </b-modal>
          <tag v-if="isAuth">
            <b-nav-item><a v-b-modal.modal-profile href="#">     <b-avatar variant="primary" v-bind:src="url + '/avatar/' + userid" size="25px"/> Profil </a></b-nav-item>
          </tag>
          <b-nav-item> <router-link to="/"> Maison </router-link></b-nav-item>
          <b-nav-item> <router-link to="/random"> Aléatoire </router-link></b-nav-item>
          <tag v-if="isAuth">
            <b-nav-item> <router-link to="/choice"> Joue </router-link></b-nav-item>
          </tag>
          <tag v-if="isAuth">
            <b-nav-item> <router-link to="/history"> Historique </router-link></b-nav-item>
          </tag>
          <tag v-if="!isAuth">
            <b-nav-item> <router-link to="/login"> Connectes-toi </router-link></b-nav-item>
          </tag>
          <tag v-if="isAuth">
            <b-nav-item><router-link to="/logout"> Déconnectes-toi </router-link></b-nav-item>
          </tag>
          <tag v-if="!isAuth">
            <b-nav-item><router-link to="/register"> Enregistres-toi </router-link></b-nav-item>
          </tag>
      </b-nav>
    </div>
    <router-view/>
  </div>
</template>

<script>
import { mapGetters } from 'vuex'
import Profile from "@/views/Profile.vue";

export default {
  name: 'App',
  components: {
    Profile,
  },
  created() {
    this.$store.dispatch('auth/autoLogin');
  },
  changed() {
    this.$store.dispatch('auth/autoLogin');
  },
  data() {
      return {
          url:process.env.VUE_APP_BACKEND_URL,
      }
  },
  computed: {
    ...mapGetters('auth', {
      isAuth: 'isAuthenticated',
      userid: "getID",
      username: 'getUsername'
    })
  },
  methods: {
    onLogout() {
      this.$store.dispatch('auth/logout');
    }
  }
}
</script>


<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

#nav {
  padding: 30px;
}

#nav a {
  font-weight: bold;
  color: #2c3e50;
}

#nav a.router-link-exact-active {
  color: #42b983;
}
</style>
