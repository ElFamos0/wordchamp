<template>
  <v-app v-bind:style="{ backgroundColor: '#0000' }">
    
    <!-- <v-modal id="modal-profile" :title="'Profil de ' + username">
      <Profile />
    </v-modal> -->
    <v-toolbar dark dense>
      <v-app-bar-nav-icon @click="drawer = true" class="d-flex d-sm-none" ></v-app-bar-nav-icon>

      <v-tabs align-with-title class="d-none d-sm-flex">

        <v-dialog transition="dialog-top-transition">
          <template v-slot:activator="{ props }">
            <v-tab v-bind="props" v-if="isAuth">
              <v-tooltip activator="parent" anchor="bottom" style="font-family: 'Roboto', sans-serif">
                Profil
              </v-tooltip>
              <b-avatar variant="primary" v-bind:src="url + '/avatar/' + userid" size="25px"/>
            </v-tab>
          </template>
          <template v-slot:default="{ isActive }">
            <v-card>
              <v-card-text>
                <v-toolbar class="mb-5" style="font-family: 'Roboto', sans-serif">Profil de {{ username }}</v-toolbar>
                <Profile />
              </v-card-text>
              <v-card-actions class="justify-end">
                <v-btn text @click="isActive.value = false" style="font-family: 'Roboto', sans-serif">Close</v-btn>
              </v-card-actions>
            </v-card>
          </template>
        </v-dialog>
        
        <v-tab to="/">
          <v-tooltip activator="parent" anchor="bottom" style="font-family: 'Roboto', sans-serif">
            Maison
          </v-tooltip>
          <font-awesome-icon icon="house" />
        </v-tab>
        <v-tab v-if="isAuth" to="/redirect">
          <v-tooltip activator="parent" anchor="bottom" style="font-family: 'Roboto', sans-serif">
            Jouer
          </v-tooltip>
          <font-awesome-icon icon="play" />
        </v-tab>
        <v-tab v-if="isAuth" to="/choicecarriere">
          <v-tooltip activator="parent" anchor="bottom" style="font-family: 'Roboto', sans-serif">
            Carrière
          </v-tooltip>
           <v-btn icon>
            <v-icon>mdi-trending-up</v-icon>
          </v-btn>
        </v-tab>
        <v-tab to="/classement" style="font-family: 'Roboto', sans-serif">
          Classement
        </v-tab>
      </v-tabs>

      <v-spacer></v-spacer>

      <v-tabs align-with-title>
        <v-tab v-if="!isAuth" to="/register">
          <v-tooltip activator="parent" anchor="bottom" style="font-family: 'Roboto', sans-serif">
            Enregistres-toi
          </v-tooltip>
          <v-btn icon>
            <v-icon>mdi-account-plus</v-icon>
          </v-btn>
        </v-tab>
        <v-tab right v-if="!isAuth" to="/login">
          <v-tooltip activator="parent" anchor="bottom" style="font-family: 'Roboto', sans-serif">
            Connecte-toi
          </v-tooltip>
          <v-btn icon>
            <v-icon>mdi-login-variant</v-icon>
          </v-btn>
        </v-tab>
        <v-tab v-if="isAuth" to="/logout">
          <v-tooltip activator="parent" anchor="bottom" style="font-family: 'Roboto', sans-serif">
            Déconnecte-toi
          </v-tooltip>
          <v-btn icon>
            <v-icon>mdi-logout-variant</v-icon>
          </v-btn>
        </v-tab>
      </v-tabs>
    </v-toolbar>
    <v-navigation-drawer v-model="drawer" absolute temporary>
      <v-list nav>
        <v-list-group>

          <v-list-item>
            <v-dialog transition="dialog-top-transition">
              <template v-slot:activator="{ props }">
                <v-tab v-bind="props" v-if="isAuth">
                  <b-avatar variant="primary" v-bind:src="url + '/avatar/' + userid" size="25px" class="mr-3"/> Profil
                </v-tab>
              </template>
              <template v-slot:default="{ isActive }">
                <v-card>
                  <v-card-text>
                    <v-toolbar class="mb-5">Profil de {{ username }}</v-toolbar>
                    <Profile />
                  </v-card-text>
                  <v-card-actions class="justify-end">
                    <v-btn text @click="isActive.value = false" style="font-family: 'Roboto', sans-serif">Close</v-btn>
                  </v-card-actions>
                </v-card>
              </template>
            </v-dialog>
          </v-list-item>

          <v-list-item>
            <v-tab to="/">
              <font-awesome-icon icon="house" class="mr-3" /> Maison
            </v-tab>
          </v-list-item>

          <v-list-item v-if="isAuth">
            <v-tab to="/redirect">
              <font-awesome-icon icon="play" class="mr-3" /> Jouer
            </v-tab>
          </v-list-item>

          <v-list-item v-if="isAuth">
            <v-tab to="/choicecarriere">
              <v-icon class="mr-3" >mdi-trending-up</v-icon> Carrière
            </v-tab>
          </v-list-item>

          <v-list-item>
            <v-tab to="/classement">
              Classement
            </v-tab>
          </v-list-item>

        </v-list-group>
      </v-list>
    </v-navigation-drawer>
    <router-view/>

  <particles-bg ref="shownBg" id="shown" type="cobweb" color="#7b1fa2" :canvas="{ backgroundColor: '#4a148c'}" :bg="true"/>
  <particles-bg ref="hiddenBg" id="hidden" type="random" color="#7b1fa2" :canvas="{ visibility:'hidden', backgroundColor: '#4a148c'}" :bg="true"/>
  </v-app>
</template>

<script>
import { mapGetters } from 'vuex';
import Profile from "@/views/Profile.vue";
import { ParticlesBg } from 'particles-bg-vue';
import axiosAuth from '@/api/axios-auth'

export default {
  name: 'App',
  components: {
    Profile,
    ParticlesBg,
  },
  mounted() {
    
    this.$store.dispatch('auth/autoLogin');
    let shownBg = this.$refs.shownBg;
    let hiddenBg = this.$refs.hiddenBg;
  
    const kode = [38, 38, 40, 40, 37, 39, 37, 39, 66, 65]
    const length = kode.length
    var pos = 0
    document.addEventListener('keydown', function (event) {
      if (event.keyCode === kode[pos++]) {
        if (length === pos) {
          // console.log(this.$refs)
          shownBg.$el.style.visibility = 'hidden'
          hiddenBg.$el.style.visibility = ''
          pos = 0 // ability to start over
          return false
        }
      } else {
        pos = 0
      }
    }, false)
  },
  created() {
    const pathCG = `${process.env.VUE_APP_BACKEND_URL}/currentGame`
    axiosAuth.get(pathCG).then((res)=> {
      this.currentGame = res.data
    })
  },
  changed() {
    this.$store.dispatch('auth/autoLogin');
  },
  data() {
      return {
        url:process.env.VUE_APP_BACKEND_URL,
        currentGame: false,
        drawer:false,
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
  color: #00341d;
}

#nav a.router-link-exact-active {
  color: #00341d;
}

.v-card {
  background-color:#aa00ff;
}

.v-toolbar {
  background-color:#aa00ff;
}
</style>