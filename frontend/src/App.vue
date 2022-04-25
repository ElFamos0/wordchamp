<template>
  <v-app>

    
    <!-- <v-modal id="modal-profile" :title="'Profil de ' + username">
      <Profile />
    </v-modal> -->
    <v-toolbar dark dense>
      <v-tabs align-with-title>

        <v-dialog transition="dialog-top-transition">
          <template v-slot:activator="{ props }">
            <v-tab v-bind="props" v-if="isAuth">
              <v-tooltip activator="parent" anchor="bottom">
                Profil
              </v-tooltip>
              <b-avatar variant="primary" v-bind:src="url + '/avatar/' + userid" size="25px"/>
            </v-tab>
          </template>
          <template v-slot:default="{ isActive }">
            <v-card>
              <v-toolbar>Profil de {{ username }}</v-toolbar>
              <v-card-text>
                <Profile />
              </v-card-text>
              <v-card-actions class="justify-end">
                <v-btn text @click="isActive.value = false" >Close</v-btn>
              </v-card-actions>
            </v-card>
          </template>
        </v-dialog>
        
        <v-tab to="/">
          <v-tooltip activator="parent" anchor="bottom">
            Maison
          </v-tooltip>
          <font-awesome-icon icon="house" />
        </v-tab>
        <v-tab v-if="isAuth" to="/choice">
          <v-tooltip activator="parent" anchor="bottom">
            Jouer
          </v-tooltip>
          <font-awesome-icon icon="play" />
        </v-tab>
        <v-tab v-if="isAuth" to="/history">
          Historique
        </v-tab>
      </v-tabs>

      <v-spacer></v-spacer>

      <v-tabs align-with-title>
        <v-tab v-if="!isAuth" to="/register">
          <v-tooltip activator="parent" anchor="bottom">
            Enregistres-toi
          </v-tooltip>
          <v-btn icon>
            <v-icon>mdi-account-plus</v-icon>
          </v-btn>
        </v-tab>
        <v-tab right v-if="!isAuth" to="/login">
          <v-tooltip activator="parent" anchor="bottom">
            Connectes-toi
          </v-tooltip>
          <v-btn icon>
            <v-icon>mdi-login-variant</v-icon>
          </v-btn>
        </v-tab>
        <v-tab v-if="isAuth" to="/logout">
          <v-tooltip activator="parent" anchor="bottom">
            Déconnecte-toi
          </v-tooltip>
          <v-btn icon>
            <v-icon>mdi-logout-variant</v-icon>
          </v-btn>
        </v-tab>
      </v-tabs>
    </v-toolbar>
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

#nav a {
  text-decoration: none;
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
