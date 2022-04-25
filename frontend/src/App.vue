<template>
  <v-app>
    <div id="nav">
      <b-nav tabs>
          <b-modal id="modal-profile" :title="'Profil de ' + username">
            <Profile />
          </b-modal>
          <tag v-if="isAuth">
            <a v-b-modal.modal-profile href="#">
              <b-nav-item>
                <b-avatar variant="primary" v-bind:src="url + '/avatar/' + userid" size="25px"/>
              </b-nav-item>
            </a>
          </tag>
          <router-link to="/">
            <b-nav-item>
              <font-awesome-icon icon="house" />
            </b-nav-item>
          </router-link>
          <tag v-if="isAuth">
            <router-link to="/choice">
              <b-nav-item id="play">
                <font-awesome-icon icon="play" />
              </b-nav-item>
            </router-link>
            <v-btn>
              Top
              <v-tooltip
                activator="parent"
                anchor="top"
              >Tooltip</v-tooltip>
            </v-btn>
          </tag>
          <tag v-if="isAuth">
            <router-link to="/history"> 
              <b-nav-item>
                Historique
              </b-nav-item>
            </router-link>
          </tag>
          <tag v-if="!isAuth">
            <router-link to="/login">
              <b-nav-item>
                Connectes-toi 
              </b-nav-item>
            </router-link>
          </tag>
          <tag v-if="isAuth">
            <router-link to="/logout">
              <b-nav-item>
              Déconnectes-toi
              </b-nav-item>
            </router-link>
          </tag>
          <tag v-if="!isAuth">
            <router-link to="/register">
              <b-nav-item>
                Enregistres-toi
              </b-nav-item>
            </router-link>
          </tag>
      </b-nav>
    </div>
    <router-view/>
  </v-app>
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

#nav a>li>a {
  font-weight: bold;
  color: #2c3e50;
}

#nav a.router-link-exact-active>li>a {
  color: #42b983;
}

#nav a.router-link-exact-active {
  color: #42b983;
}
</style>
